#pragma once

#include "SPTabBarViewElement.h"

#include <string>

namespace space {
class SPTableElement;
class PlayQueueDataSource;

namespace views {

/**
 * PlayQueueView  —  right-sidebar panel
 *
 * A SPTabBarViewElement with a single "Play queue" tab that displays
 * the current now-playing queue as an SPTableElement.
 */
class PlayQueueView : public SPTabBarViewElement {
public:
    PlayQueueView();
    explicit PlayQueueView(SPElement* parent);
    ~PlayQueueView() override;

    std::string getType() override { return "playqueueview"; }

    /** Refresh the table from SpacifyApp's current now-playing queue. */
    void reload();

private:
    SPTableElement*      m_table      = nullptr;
    PlayQueueDataSource* m_dataSource = nullptr;
};

} // namespace views
} // namespace space
