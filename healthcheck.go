// Sends "/info" request to the localhosted core,
// if info['state'] == 'Synced!' returns 0, otherwise returns 1.
// Gets config path from CONFIG env variable
// Loads HTTP_PORT from CONFIG file, otherwise sets it to 8080.

package main

import (
	"encoding/json"
	"fmt"
	"io"
	"log"
	"net/http"
	"os"
	"strings"

	"gopkg.in/ini.v1"
)

const(
	defaultConfigPath = "/config.ini"
	healthyState = "Synced!"
	defaultCorePort = 8080

	stateEndpoint = "http://localhost:%d/info"
)

func main() {
	configPath := os.Getenv("CONFIG")
	if configPath == "" {
		configPath = defaultConfigPath
	}

	corePort := getCorePort(configPath)
	state, err := coreState(fmt.Sprintf(stateEndpoint, corePort))
	if err != nil {
		log.Fatalf("failed to get core info: %v", err)
	}

	if !strings.EqualFold(state, healthyState) {
		log.Fatalf("node is in bad state: %s", state)
	}

	log.Printf("node is in good state")
}

func coreState(coreUrl string) (string, error) {
	response, err := http.Get(coreUrl)
	if err != nil {
		return "", fmt.Errorf("failed to get info: %v", err)
	}
	defer response.Body.Close()

	return stateFromResponse(response.Body)
}

func getCorePort(configPath string) (int) {
	cfg, err := ini.LoadSources( ini.LoadOptions{
			SkipUnrecognizableLines: true,
		}, configPath)

    if err != nil {
		return defaultCorePort
	}

	return cfg.Section("").Key("HTTP_PORT").MustInt(defaultCorePort)
}

func stateFromResponse(r io.Reader) (string, error) {
	var coreResponse struct {
		Info struct {
			State string
		}
	}

	if err := json.NewDecoder(r).Decode(&coreResponse); err != nil {
		return "", fmt.Errorf("failed to decode core response: %v", err)
	}

	return coreResponse.Info.State, nil
}

