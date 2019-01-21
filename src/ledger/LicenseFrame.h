#include "EntryFrame.h"

namespace soci
{
    class session;
}
namespace stellar
{

    class LicenseFrame : public EntryFrame {

        LicenseEntry& mLicense;

        LicenseFrame(LicenseFrame const& from);

    public:
        typedef std::shared_ptr<LicenseFrame> pointer;

        static pointer createNew(Hash ledgerHash, Hash licenseHash,
                uint64_t adminCount, uint64_t dueDate, xdr::xvector<DecoratedSignature, 2> signatures);

        LicenseFrame();
        LicenseFrame(LedgerEntry const& from);

        LicenseFrame& operator=(LicenseFrame const& other);

        EntryFrame::pointer
        copy() const override
        {
            return EntryFrame::pointer(new LicenseFrame(*this));
        }
        LicenseEntry& getLicenseEntry();
    };
}
