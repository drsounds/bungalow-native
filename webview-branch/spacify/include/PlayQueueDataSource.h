#pragma once

#include "SPTableDataSource.h"

#include "models/SPPlayable.h"

#include <string>
#include <vector>

namespace space {

/**
 * PlayQueueDataSource
 *
 * Provides the now-playing queue (a vector of SPPlayable*) to an SPTableElement.
 * Exposes a single column showing each playable's URI.
 */
class PlayQueueDataSource : public SPTableDataSource {
public:
    PlayQueueDataSource() = default;
    ~PlayQueueDataSource() override = default;

    int         getColumnCount()                    override { return 1; }
    int         getRowCount()                       override;
    std::string getTextForCell(int column, int row) override;
    std::string getTextForColumn(int column)        override;

    /** Replace the displayed queue (non-owning view of the pointers). */
    void setQueue(const std::vector<SPPlayable*>& queue);

private:
    std::vector<SPPlayable*> m_queue;
};

} // namespace space
