// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the Apache License, Version 2.0. See the COPYING file at the root
// of this distribution or at http://www.apache.org/licenses/LICENSE-2.0

#include "crypto/KeyUtils.h"
#include "crypto/SecretKey.h"
#include "lib/catch.hpp"
#include "main/Application.h"
#include "main/Config.h"
#include "overlay/BanManager.h"
#include "overlay/LoopbackPeer.h"
#include "overlay/OverlayManagerImpl.h"
#include "overlay/PeerManager.h"
#include "overlay/TCPPeer.h"
#include "simulation/Simulation.h"
#include "test/TestUtils.h"
#include "test/test.h"
#include "util/Logging.h"
#include "util/Timer.h"

#include "medida/meter.h"
#include "medida/metrics_registry.h"
#include "medida/timer.h"
#include "util/format.h"
#include <numeric>

using namespace stellar;

TEST_CASE("loopback peer hello", "[overlay][connections]")
{
    VirtualClock clock;
    Config const& cfg1 = getTestConfig(0);
    Config const& cfg2 = getTestConfig(1);
    auto app1 = createTestApplication(clock, cfg1);
    auto app2 = createTestApplication(clock, cfg2);

    LoopbackPeerConnection conn(*app1, *app2);
    testutil::crankSome(clock);

    REQUIRE(conn.getInitiator()->isAuthenticated());
    REQUIRE(conn.getAcceptor()->isAuthenticated());
}

TEST_CASE("loopback peer with 0 port", "[overlay][connections]")
{
    VirtualClock clock;
    auto const& cfg1 = getTestConfig(0);
    auto cfg2 = getTestConfig(1);
    cfg2.PEER_PORT = 0;

    auto app1 = createTestApplication(clock, cfg1);
    auto app2 = createTestApplication(clock, cfg2);

    LoopbackPeerConnection conn(*app1, *app2);
    testutil::crankSome(clock);

    REQUIRE(!conn.getInitiator()->isAuthenticated());
    REQUIRE(!conn.getAcceptor()->isAuthenticated());
}

TEST_CASE("loopback peer send auth before hello", "[overlay][connections]")
{
    VirtualClock clock;
    auto const& cfg1 = getTestConfig(0);
    auto const& cfg2 = getTestConfig(1);
    auto app1 = createTestApplication(clock, cfg1);
    auto app2 = createTestApplication(clock, cfg2);

    LoopbackPeerConnection conn(*app1, *app2);
    conn.getInitiator()->sendAuth();
    testutil::crankSome(clock);

    REQUIRE(!conn.getInitiator()->isAuthenticated());
    REQUIRE(!conn.getAcceptor()->isAuthenticated());
}

TEST_CASE("failed auth", "[overlay][connections]")
{
    VirtualClock clock;
    Config const& cfg1 = getTestConfig(0);
    Config const& cfg2 = getTestConfig(1);
    auto app1 = createTestApplication(clock, cfg1);
    auto app2 = createTestApplication(clock, cfg2);

    LoopbackPeerConnection conn(*app1, *app2);
    conn.getInitiator()->setDamageAuth(true);
    testutil::crankSome(clock);

    REQUIRE(!conn.getInitiator()->isConnected());
    REQUIRE(!conn.getAcceptor()->isConnected());
    REQUIRE(conn.getInitiator()->getDropReason() == "unexpected MAC");
}

TEST_CASE("reject non preferred peer", "[overlay][connections]")
{
    VirtualClock clock;
    Config const& cfg1 = getTestConfig(0);
    Config cfg2 = getTestConfig(1);

    cfg2.PREFERRED_PEERS_ONLY = true;

    auto app1 = createTestApplication(clock, cfg1);
    auto app2 = createTestApplication(clock, cfg2);

    SECTION("inbound")
    {
        LoopbackPeerConnection conn(*app1, *app2);
        testutil::crankSome(clock);

        REQUIRE(!conn.getInitiator()->isConnected());
        REQUIRE(!conn.getAcceptor()->isConnected());
        REQUIRE(conn.getAcceptor()->getDropReason() == "peer rejected");
    }

    SECTION("outbound")
    {
        LoopbackPeerConnection conn(*app2, *app1);
        testutil::crankSome(clock);

        REQUIRE(!conn.getInitiator()->isConnected());
        REQUIRE(!conn.getAcceptor()->isConnected());
        REQUIRE(conn.getInitiator()->getDropReason() == "peer rejected");
    }
}

TEST_CASE("accept preferred peer even when strict", "[overlay][connections]")
{
    VirtualClock clock;
    Config const& cfg1 = getTestConfig(0);
    Config cfg2 = getTestConfig(1);

    cfg2.PREFERRED_PEERS_ONLY = true;
    cfg2.PREFERRED_PEER_KEYS.push_back(
        KeyUtils::toStrKey(cfg1.NODE_SEED.getPublicKey()));

    auto app1 = createTestApplication(clock, cfg1);
    auto app2 = createTestApplication(clock, cfg2);

    SECTION("inbound")
    {
        LoopbackPeerConnection conn(*app1, *app2);
        testutil::crankSome(clock);

        REQUIRE(conn.getInitiator()->isAuthenticated());
        REQUIRE(conn.getAcceptor()->isAuthenticated());
    }

    SECTION("outbound")
    {
        LoopbackPeerConnection conn(*app2, *app1);
        testutil::crankSome(clock);

        REQUIRE(conn.getInitiator()->isAuthenticated());
        REQUIRE(conn.getAcceptor()->isAuthenticated());
    }
}

TEST_CASE("reject peers beyond max", "[overlay][connections]")
{
    VirtualClock clock;
    Config const& cfg1 = getTestConfig(0);
    Config cfg2 = getTestConfig(1);
    Config const& cfg3 = getTestConfig(2);

    SECTION("inbound")
    {
        cfg2.MAX_ADDITIONAL_PEER_CONNECTIONS = 1;
        cfg2.TARGET_PEER_CONNECTIONS = 0;

        auto app1 = createTestApplication(clock, cfg1);
        auto app2 = createTestApplication(clock, cfg2);
        auto app3 = createTestApplication(clock, cfg3);

        LoopbackPeerConnection conn1(*app1, *app2);
        LoopbackPeerConnection conn2(*app3, *app2);
        testutil::crankSome(clock);

        REQUIRE(conn1.getInitiator()->isConnected());
        REQUIRE(conn1.getAcceptor()->isConnected());
        REQUIRE(!conn2.getInitiator()->isConnected());
        REQUIRE(!conn2.getAcceptor()->isConnected());
        REQUIRE(conn2.getAcceptor()->getDropReason() == "peer rejected");
    }

    SECTION("outbound")
    {
        cfg2.MAX_ADDITIONAL_PEER_CONNECTIONS = 0;
        cfg2.TARGET_PEER_CONNECTIONS = 1;

        auto app1 = createTestApplication(clock, cfg1);
        auto app2 = createTestApplication(clock, cfg2);
        auto app3 = createTestApplication(clock, cfg3);

        LoopbackPeerConnection conn1(*app2, *app1);
        LoopbackPeerConnection conn2(*app2, *app3);
        testutil::crankSome(clock);

        REQUIRE(conn1.getInitiator()->isConnected());
        REQUIRE(conn1.getAcceptor()->isConnected());
        REQUIRE(!conn2.getInitiator()->isConnected());
        REQUIRE(!conn2.getAcceptor()->isConnected());
        REQUIRE(conn2.getInitiator()->getDropReason() == "peer rejected");
    }
}

TEST_CASE("reject peers beyond max - preferred peer wins",
          "[overlay][connections]")
{
    VirtualClock clock;
    Config const& cfg1 = getTestConfig(0);
    Config cfg2 = getTestConfig(1);
    Config const& cfg3 = getTestConfig(2);

    SECTION("preferred connects first")
    {
        SECTION("inbound")
        {
            cfg2.MAX_ADDITIONAL_PEER_CONNECTIONS = 1;
            cfg2.TARGET_PEER_CONNECTIONS = 0;
            cfg2.PREFERRED_PEER_KEYS.push_back(
                KeyUtils::toStrKey(cfg3.NODE_SEED.getPublicKey()));

            auto app1 = createTestApplication(clock, cfg1);
            auto app2 = createTestApplication(clock, cfg2);
            auto app3 = createTestApplication(clock, cfg3);

            LoopbackPeerConnection conn2(*app3, *app2);
            LoopbackPeerConnection conn1(*app1, *app2);
            testutil::crankSome(clock);

            REQUIRE(!conn1.getInitiator()->isConnected());
            REQUIRE(!conn1.getAcceptor()->isConnected());
            REQUIRE(conn2.getInitiator()->isConnected());
            REQUIRE(conn2.getAcceptor()->isConnected());
            REQUIRE(conn1.getAcceptor()->getDropReason() == "peer rejected");
        }

        SECTION("outbound")
        {
            cfg2.MAX_ADDITIONAL_PEER_CONNECTIONS = 0;
            cfg2.TARGET_PEER_CONNECTIONS = 1;
            cfg2.PREFERRED_PEER_KEYS.push_back(
                KeyUtils::toStrKey(cfg3.NODE_SEED.getPublicKey()));

            auto app1 = createTestApplication(clock, cfg1);
            auto app2 = createTestApplication(clock, cfg2);
            auto app3 = createTestApplication(clock, cfg3);

            LoopbackPeerConnection conn2(*app2, *app3);
            LoopbackPeerConnection conn1(*app2, *app1);
            testutil::crankSome(clock);

            REQUIRE(!conn1.getInitiator()->isConnected());
            REQUIRE(!conn1.getAcceptor()->isConnected());
            REQUIRE(conn2.getInitiator()->isConnected());
            REQUIRE(conn2.getAcceptor()->isConnected());
            REQUIRE(conn1.getInitiator()->getDropReason() == "peer rejected");
        }
    }

    SECTION("preferred connects second")
    {
        SECTION("inbound")
        {
            cfg2.MAX_ADDITIONAL_PEER_CONNECTIONS = 1;
            cfg2.TARGET_PEER_CONNECTIONS = 0;
            cfg2.PREFERRED_PEER_KEYS.push_back(
                KeyUtils::toStrKey(cfg3.NODE_SEED.getPublicKey()));

            auto app1 = createTestApplication(clock, cfg1);
            auto app2 = createTestApplication(clock, cfg2);
            auto app3 = createTestApplication(clock, cfg3);

            LoopbackPeerConnection conn1(*app1, *app2);
            LoopbackPeerConnection conn2(*app3, *app2);
            testutil::crankSome(clock);

            REQUIRE(!conn1.getInitiator()->isConnected());
            REQUIRE(!conn1.getAcceptor()->isConnected());
            REQUIRE(conn2.getInitiator()->isConnected());
            REQUIRE(conn2.getAcceptor()->isConnected());
            REQUIRE(conn1.getAcceptor()->getDropReason() ==
                    "preferred peer selected instead");
        }

        SECTION("outbound")
        {
            cfg2.MAX_ADDITIONAL_PEER_CONNECTIONS = 0;
            cfg2.TARGET_PEER_CONNECTIONS = 1;
            cfg2.PREFERRED_PEER_KEYS.push_back(
                KeyUtils::toStrKey(cfg3.NODE_SEED.getPublicKey()));

            auto app1 = createTestApplication(clock, cfg1);
            auto app2 = createTestApplication(clock, cfg2);
            auto app3 = createTestApplication(clock, cfg3);

            LoopbackPeerConnection conn1(*app2, *app1);
            LoopbackPeerConnection conn2(*app2, *app3);
            testutil::crankSome(clock);

            REQUIRE(!conn1.getInitiator()->isConnected());
            REQUIRE(!conn1.getAcceptor()->isConnected());
            REQUIRE(conn2.getInitiator()->isConnected());
            REQUIRE(conn2.getAcceptor()->isConnected());
            REQUIRE(conn1.getInitiator()->getDropReason() ==
                    "preferred peer selected instead");
        }
    }
}

TEST_CASE("allow inbound pending peers up to max", "[overlay][connections]")
{
    VirtualClock clock;
    Config const& cfg1 = getTestConfig(0);
    Config cfg2 = getTestConfig(1);
    Config const& cfg3 = getTestConfig(2);
    Config const& cfg4 = getTestConfig(3);
    Config const& cfg5 = getTestConfig(4);

    cfg2.MAX_INBOUND_PENDING_CONNECTIONS = 3;
    cfg2.MAX_OUTBOUND_PENDING_CONNECTIONS = 3;

    auto app1 = createTestApplication(clock, cfg1);
    auto app2 = createTestApplication(clock, cfg2);
    auto app3 = createTestApplication(clock, cfg3);
    auto app4 = createTestApplication(clock, cfg4);
    auto app5 = createTestApplication(clock, cfg5);

    LoopbackPeerConnection conn1(*app1, *app2);
    REQUIRE(conn1.getInitiator()->getState() == Peer::CONNECTED);
    REQUIRE(conn1.getAcceptor()->getState() == Peer::CONNECTED);
    conn1.getInitiator()->setCorked(true);

    LoopbackPeerConnection conn2(*app3, *app2);
    REQUIRE(conn2.getInitiator()->getState() == Peer::CONNECTED);
    REQUIRE(conn2.getAcceptor()->getState() == Peer::CONNECTED);
    conn2.getInitiator()->setCorked(true);

    LoopbackPeerConnection conn3(*app4, *app2);
    REQUIRE(conn3.getInitiator()->getState() == Peer::CONNECTED);
    REQUIRE(conn3.getAcceptor()->getState() == Peer::CONNECTED);

    LoopbackPeerConnection conn4(*app5, *app2);
    REQUIRE(conn4.getInitiator()->getState() == Peer::CONNECTED);
    REQUIRE(conn4.getAcceptor()->getState() == Peer::CLOSING);

    testutil::crankSome(clock);

    REQUIRE(conn1.getInitiator()->getState() == Peer::CLOSING);
    REQUIRE(conn1.getAcceptor()->getState() == Peer::CLOSING);
    REQUIRE(conn2.getInitiator()->getState() == Peer::CLOSING);
    REQUIRE(conn2.getAcceptor()->getState() == Peer::CLOSING);
    REQUIRE(conn3.getInitiator()->isConnected());
    REQUIRE(conn3.getAcceptor()->isConnected());
    REQUIRE(conn4.getInitiator()->getState() == Peer::CLOSING);
    REQUIRE(conn4.getAcceptor()->getState() == Peer::CLOSING);
    REQUIRE(app2->getMetrics()
                .NewMeter({"overlay", "timeout", "idle"}, "timeout")
                .count() == 2);
}

TEST_CASE("allow inbound pending peers over max if possibly preferred",
          "[overlay][connections]")
{
    VirtualClock clock;
    Config const& cfg1 = getTestConfig(0);
    Config cfg2 = getTestConfig(1);
    Config const& cfg3 = getTestConfig(2);
    Config const& cfg4 = getTestConfig(3);
    Config const& cfg5 = getTestConfig(4);

    cfg2.MAX_INBOUND_PENDING_CONNECTIONS = 3;
    cfg2.MAX_OUTBOUND_PENDING_CONNECTIONS = 3;
    cfg2.PREFERRED_PEERS.emplace_back("127.0.0.1:17");

    auto app1 = createTestApplication(clock, cfg1);
    auto app2 = createTestApplication(clock, cfg2);
    auto app3 = createTestApplication(clock, cfg3);
    auto app4 = createTestApplication(clock, cfg4);
    auto app5 = createTestApplication(clock, cfg5);

    (static_cast<OverlayManagerImpl&>(app2->getOverlayManager()))
        .storeConfigPeers();

    LoopbackPeerConnection conn1(*app1, *app2);
    REQUIRE(conn1.getInitiator()->getState() == Peer::CONNECTED);
    REQUIRE(conn1.getAcceptor()->getState() == Peer::CONNECTED);
    conn1.getInitiator()->setCorked(true);

    LoopbackPeerConnection conn2(*app3, *app2);
    REQUIRE(conn2.getInitiator()->getState() == Peer::CONNECTED);
    REQUIRE(conn2.getAcceptor()->getState() == Peer::CONNECTED);
    conn2.getInitiator()->setCorked(true);

    LoopbackPeerConnection conn3(*app4, *app2);
    REQUIRE(conn3.getInitiator()->getState() == Peer::CONNECTED);
    REQUIRE(conn3.getAcceptor()->getState() == Peer::CONNECTED);

    LoopbackPeerConnection conn4(*app5, *app2);
    REQUIRE(conn4.getInitiator()->getState() == Peer::CONNECTED);
    REQUIRE(conn4.getAcceptor()->getState() == Peer::CONNECTED);

    testutil::crankSome(clock);

    REQUIRE(conn1.getInitiator()->getState() == Peer::CLOSING);
    REQUIRE(conn1.getAcceptor()->getState() == Peer::CLOSING);
    REQUIRE(conn2.getInitiator()->getState() == Peer::CLOSING);
    REQUIRE(conn2.getAcceptor()->getState() == Peer::CLOSING);
    REQUIRE(conn3.getInitiator()->isConnected());
    REQUIRE(conn3.getAcceptor()->isConnected());
    REQUIRE(conn4.getInitiator()->isConnected());
    REQUIRE(conn4.getAcceptor()->isConnected());
    REQUIRE(app2->getMetrics()
                .NewMeter({"overlay", "timeout", "idle"}, "timeout")
                .count() == 2);
    REQUIRE(app2->getMetrics()
                .NewMeter({"overlay", "connection", "reject"}, "connection")
                .count() == 0);
}

TEST_CASE("allow outbound pending peers up to max", "[overlay][connections]")
{
    VirtualClock clock;
    Config const& cfg1 = getTestConfig(0);
    Config cfg2 = getTestConfig(1);
    Config const& cfg3 = getTestConfig(2);
    Config const& cfg4 = getTestConfig(3);
    Config const& cfg5 = getTestConfig(4);

    cfg2.MAX_INBOUND_PENDING_CONNECTIONS = 3;
    cfg2.MAX_OUTBOUND_PENDING_CONNECTIONS = 3;

    auto app1 = createTestApplication(clock, cfg1);
    auto app2 = createTestApplication(clock, cfg2);
    auto app3 = createTestApplication(clock, cfg3);
    auto app4 = createTestApplication(clock, cfg4);
    auto app5 = createTestApplication(clock, cfg5);

    LoopbackPeerConnection conn1(*app2, *app1);
    REQUIRE(conn1.getInitiator()->getState() == Peer::CONNECTED);
    REQUIRE(conn1.getAcceptor()->getState() == Peer::CONNECTED);
    conn1.getInitiator()->setCorked(true);

    LoopbackPeerConnection conn2(*app2, *app3);
    REQUIRE(conn2.getInitiator()->getState() == Peer::CONNECTED);
    REQUIRE(conn2.getAcceptor()->getState() == Peer::CONNECTED);
    conn2.getInitiator()->setCorked(true);

    LoopbackPeerConnection conn3(*app2, *app4);
    REQUIRE(conn3.getInitiator()->getState() == Peer::CONNECTED);
    REQUIRE(conn3.getAcceptor()->getState() == Peer::CONNECTED);

    LoopbackPeerConnection conn4(*app2, *app5);
    REQUIRE(conn4.getInitiator()->getState() == Peer::CLOSING);
    REQUIRE(conn4.getAcceptor()->getState() == Peer::CONNECTED);
    conn2.getInitiator()->setCorked(true);

    testutil::crankSome(clock);

    REQUIRE(conn1.getInitiator()->getState() == Peer::CLOSING);
    REQUIRE(conn1.getAcceptor()->getState() == Peer::CLOSING);
    REQUIRE(conn2.getInitiator()->getState() == Peer::CLOSING);
    REQUIRE(conn2.getAcceptor()->getState() == Peer::CLOSING);
    REQUIRE(conn3.getInitiator()->isConnected());
    REQUIRE(conn3.getAcceptor()->isConnected());
    REQUIRE(conn4.getInitiator()->getState() == Peer::CLOSING);
    REQUIRE(conn4.getAcceptor()->getState() == Peer::CLOSING);
    REQUIRE(app2->getMetrics()
                .NewMeter({"overlay", "timeout", "idle"}, "timeout")
                .count() == 2);
}

TEST_CASE("reject peers with differing network passphrases",
          "[overlay][connections]")
{
    VirtualClock clock;
    Config const& cfg1 = getTestConfig(0);
    Config cfg2 = getTestConfig(1);

    cfg2.NETWORK_PASSPHRASE = "nothing to see here";

    auto app1 = createTestApplication(clock, cfg1);
    auto app2 = createTestApplication(clock, cfg2);

    LoopbackPeerConnection conn(*app1, *app2);
    testutil::crankSome(clock);

    REQUIRE(!conn.getInitiator()->isConnected());
    REQUIRE(!conn.getAcceptor()->isConnected());
}

TEST_CASE("reject peers with invalid cert", "[overlay][connections]")
{
    VirtualClock clock;
    Config const& cfg1 = getTestConfig(0);
    Config cfg2 = getTestConfig(1);

    auto app1 = createTestApplication(clock, cfg1);
    auto app2 = createTestApplication(clock, cfg2);

    LoopbackPeerConnection conn(*app1, *app2);
    conn.getAcceptor()->setDamageCert(true);
    testutil::crankSome(clock);

    REQUIRE(!conn.getInitiator()->isConnected());
    REQUIRE(!conn.getAcceptor()->isConnected());
}

TEST_CASE("reject banned peers", "[overlay][connections]")
{
    VirtualClock clock;
    Config const& cfg1 = getTestConfig(0);
    Config cfg2 = getTestConfig(1);

    auto app1 = createTestApplication(clock, cfg1);
    auto app2 = createTestApplication(clock, cfg2);
    app1->getBanManager().banNode(cfg2.NODE_SEED.getPublicKey());

    LoopbackPeerConnection conn(*app1, *app2);
    testutil::crankSome(clock);

    REQUIRE(!conn.getInitiator()->isConnected());
    REQUIRE(!conn.getAcceptor()->isConnected());
}

TEST_CASE("reject peers with incompatible overlay versions",
          "[overlay][connections]")
{
    Config const& cfg1 = getTestConfig(0);

    auto doVersionCheck = [&](uint32 version) {
        VirtualClock clock;
        Config cfg2 = getTestConfig(1);

        cfg2.OVERLAY_PROTOCOL_MIN_VERSION = version;
        cfg2.OVERLAY_PROTOCOL_VERSION = version;
        auto app1 = createTestApplication(clock, cfg1);
        auto app2 = createTestApplication(clock, cfg2);

        LoopbackPeerConnection conn(*app1, *app2);
        testutil::crankSome(clock);

        REQUIRE(!conn.getInitiator()->isConnected());
        REQUIRE(!conn.getAcceptor()->isConnected());
        REQUIRE(conn.getInitiator()->getDropReason() ==
                "wrong protocol version");
    };
    SECTION("cfg2 above")
    {
        doVersionCheck(cfg1.OVERLAY_PROTOCOL_VERSION + 1);
    }
    SECTION("cfg2 below")
    {
        doVersionCheck(cfg1.OVERLAY_PROTOCOL_MIN_VERSION - 1);
    }
}

TEST_CASE("reject peers who dont handshake quickly", "[overlay][connections]")
{
    auto test = [](unsigned short authenticationTimeout) {
        VirtualClock clock;
        Config cfg1 = getTestConfig(0);
        Config cfg2 = getTestConfig(1);

        cfg1.PEER_AUTHENTICATION_TIMEOUT = authenticationTimeout;
        cfg2.PEER_AUTHENTICATION_TIMEOUT = authenticationTimeout;

        auto app1 = createTestApplication(clock, cfg1);
        auto app2 = createTestApplication(clock, cfg2);
        auto waitTime = std::chrono::seconds(authenticationTimeout + 1);
        auto padTime = std::chrono::seconds(2);

        LoopbackPeerConnection conn(*app1, *app2);
        conn.getInitiator()->setCorked(true);
        auto start = clock.now();
        while (clock.now() < (start + waitTime) &&
               conn.getInitiator()->isConnected() &&
               conn.getAcceptor()->isConnected())
        {
            LOG(INFO) << "clock.now() = "
                      << clock.now().time_since_epoch().count();
            clock.crank(false);
        }
        REQUIRE(clock.now() < (start + waitTime + padTime));
        REQUIRE(!conn.getInitiator()->isConnected());
        REQUIRE(!conn.getAcceptor()->isConnected());
        REQUIRE(app2->getMetrics()
                    .NewMeter({"overlay", "timeout", "idle"}, "timeout")
                    .count() != 0);
    };

    SECTION("2 seconds timeout")
    {
        test(2);
    }

    SECTION("5 seconds timeout")
    {
        test(5);
    }
}

TEST_CASE("reject peers with the same nodeid", "[overlay][connections]")
{
    VirtualClock clock;
    Config const& cfg1 = getTestConfig(0);
    Config const& cfg2 = getTestConfig(1);
    Config cfg3 = getTestConfig(2);

    cfg3.NODE_SEED = cfg1.NODE_SEED;

    auto app1 = createTestApplication(clock, cfg1);
    auto app2 = createTestApplication(clock, cfg2);
    auto app3 = createTestApplication(clock, cfg3);

    LoopbackPeerConnection conn(*app1, *app2);
    LoopbackPeerConnection conn2(*app3, *app2);
    testutil::crankSome(clock);

    REQUIRE(conn.getInitiator()->isAuthenticated());
    REQUIRE(conn.getAcceptor()->isAuthenticated());
    REQUIRE(!conn2.getInitiator()->isConnected());
    REQUIRE(!conn2.getAcceptor()->isConnected());
    REQUIRE(conn2.getAcceptor()->getDropReason() ==
            "connecting already-connected peer");
}

TEST_CASE("connecting to saturated nodes", "[overlay][connections]")
{
    auto networkID = sha256(getTestConfig().NETWORK_PASSPHRASE);
    auto simulation =
        std::make_shared<Simulation>(Simulation::OVER_TCP, networkID);

    auto getConfiguration = [](int id, unsigned short targetOutboundConnections,
                               unsigned short maxInboundConnections) {
        auto cfg = getTestConfig(id);
        cfg.TARGET_PEER_CONNECTIONS = targetOutboundConnections;
        cfg.MAX_ADDITIONAL_PEER_CONNECTIONS = maxInboundConnections;
        return cfg;
    };

    auto numberOfAppConnections = [](Application& app) {
        return app.getOverlayManager().getAuthenticatedPeersCount();
    };

    auto numberOfSimulationConnections = [&]() {
        auto nodes = simulation->getNodes();
        return std::accumulate(std::begin(nodes), std::end(nodes), 0,
                               [&](int x, Application::pointer app) {
                                   return x + numberOfAppConnections(*app);
                               });
    };

    auto headCfg = getConfiguration(1, 0, 1);
    auto node1Cfg = getConfiguration(2, 1, 1);
    auto node2Cfg = getConfiguration(3, 1, 1);
    auto node3Cfg = getConfiguration(4, 1, 1);

    SIMULATION_CREATE_NODE(Head);
    SIMULATION_CREATE_NODE(Node1);
    SIMULATION_CREATE_NODE(Node2);
    SIMULATION_CREATE_NODE(Node3);

    SCPQuorumSet qSet;
    qSet.threshold = 2;
    qSet.validators.push_back(vHeadNodeID);
    qSet.validators.push_back(vNode1NodeID);
    qSet.validators.push_back(vNode2NodeID);
    qSet.validators.push_back(vNode3NodeID);

    auto headId = simulation->addNode(vHeadSecretKey, qSet, &headCfg)
                      ->getConfig()
                      .NODE_SEED.getPublicKey();
    simulation->addNode(vNode1SecretKey, qSet, &node1Cfg);
    simulation->addNode(vNode2SecretKey, qSet, &node2Cfg);
    simulation->addNode(vNode3SecretKey, qSet, &node3Cfg);

    simulation->addPendingConnection(vNode1NodeID, vHeadNodeID);
    simulation->addPendingConnection(vNode2NodeID, vHeadNodeID);
    simulation->addPendingConnection(vNode3NodeID, vHeadNodeID);

    simulation->startAllNodes();
    simulation->crankForAtLeast(std::chrono::seconds{15}, false);
    simulation->removeNode(headId);
    simulation->crankForAtLeast(std::chrono::seconds{15}, false);

    // all three (two-way) connections are made
    REQUIRE(numberOfSimulationConnections() == 6);
    simulation->crankForAtLeast(std::chrono::seconds{1}, true);
}

TEST_CASE("inbounds nodes can be promoted to ouboundvalid", "[overlay]")
{
    auto networkID = sha256(getTestConfig().NETWORK_PASSPHRASE);
    auto simulation =
        std::make_shared<Simulation>(Simulation::OVER_TCP, networkID);

    SIMULATION_CREATE_NODE(Node1);
    SIMULATION_CREATE_NODE(Node2);
    SIMULATION_CREATE_NODE(Node3);

    SCPQuorumSet qSet;
    qSet.threshold = 1;
    qSet.validators.push_back(vNode1NodeID);

    auto nodes = std::vector<Application::pointer>{};
    auto configs = std::vector<Config>{};
    auto addresses = std::vector<PeerBareAddress>{};
    for (auto i = 0; i < 3; i++)
    {
        configs.push_back(getTestConfig(i + 1));
        addresses.emplace_back("127.0.0.1", configs[i].PEER_PORT);
    }

    configs[0].KNOWN_PEERS.emplace_back(
        fmt::format("127.0.0.1:{}", configs[1].PEER_PORT));
    configs[2].KNOWN_PEERS.emplace_back(
        fmt::format("127.0.0.1:{}", configs[0].PEER_PORT));

    nodes.push_back(simulation->addNode(vNode1SecretKey, qSet, &configs[0]));
    nodes.push_back(simulation->addNode(vNode2SecretKey, qSet, &configs[1]));
    nodes.push_back(simulation->addNode(vNode3SecretKey, qSet, &configs[2]));

    enum class TestPeerType
    {
        ANY,
        KNOWN,
        OUTBOUND
    };

    auto getTestPeerType = [&](int i, int j) {
        auto& node = nodes[i];
        auto peer =
            node->getOverlayManager().getPeerManager().load(addresses[j]);
        if (!peer.second)
        {
            return TestPeerType::ANY;
        }

        return peer.first.mType == static_cast<int>(PeerType::INBOUND)
                   ? TestPeerType::KNOWN
                   : TestPeerType::OUTBOUND;
    };

    using ExpectedResultType = std::vector<std::vector<TestPeerType>>;
    auto peerTypesMatch = [&](ExpectedResultType expected) {
        for (auto i = 0; i < expected.size(); i++)
        {
            for (auto j = 0; j < expected[i].size(); j++)
            {
                if (expected[i][j] > getTestPeerType(i, j))
                {
                    return false;
                }
            }
        }
        return true;
    };

    simulation->startAllNodes();

    // at first, nodes only know about KNOWN_PEERS
    simulation->crankUntil(
        [&] {
            return peerTypesMatch(
                {{TestPeerType::ANY, TestPeerType::KNOWN, TestPeerType::ANY},
                 {TestPeerType::ANY, TestPeerType::ANY, TestPeerType::ANY},
                 {TestPeerType::KNOWN, TestPeerType::ANY, TestPeerType::ANY}});
        },
        std::chrono::seconds(2), false);

    // then, after connection, some are made OUTBOUND
    simulation->crankUntil(
        [&] {
            return peerTypesMatch(
                {{TestPeerType::ANY, TestPeerType::OUTBOUND,
                  TestPeerType::KNOWN},
                 {TestPeerType::KNOWN, TestPeerType::ANY, TestPeerType::ANY},
                 {TestPeerType::OUTBOUND, TestPeerType::ANY,
                  TestPeerType::ANY}});
        },
        std::chrono::seconds(10), false);

    // then, after promotion, more are made OUTBOUND
    simulation->crankUntil(
        [&] {
            return peerTypesMatch(
                {{TestPeerType::ANY, TestPeerType::OUTBOUND,
                  TestPeerType::OUTBOUND},
                 {TestPeerType::OUTBOUND, TestPeerType::ANY, TestPeerType::ANY},
                 {TestPeerType::OUTBOUND, TestPeerType::ANY,
                  TestPeerType::ANY}});
        },
        std::chrono::seconds(30), false);

    // and when all connections are made, all nodes know about each other
    simulation->crankUntil(
        [&] {
            return peerTypesMatch(
                {{TestPeerType::ANY, TestPeerType::OUTBOUND,
                  TestPeerType::OUTBOUND},
                 {TestPeerType::OUTBOUND, TestPeerType::ANY,
                  TestPeerType::OUTBOUND},
                 {TestPeerType::OUTBOUND, TestPeerType::OUTBOUND,
                  TestPeerType::ANY}});
        },
        std::chrono::seconds(30), false);

    simulation->crankForAtLeast(std::chrono::seconds{3}, true);
}
