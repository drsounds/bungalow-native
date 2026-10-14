#include "PlayQueueDataSource.h"
#include "models/SPPlayable.h"

namespace space {

int PlayQueueDataSource::getRowCount() {
    return static_cast<int>(m_queue.size());
}

std::string PlayQueueDataSource::getTextForColumn(int /*column*/) {
    return "Track";
}

std::string PlayQueueDataSource::getTextForCell(int /*column*/, int row) {
    if (row < 0 || row >= static_cast<int>(m_queue.size())) return "";
    const SPPlayable* p = m_queue[row];
    return p ? p->uri : "";
}

void PlayQueueDataSource::setQueue(const std::vector<SPPlayable*>& queue) {
    m_queue = queue;
}

} // namespace space
