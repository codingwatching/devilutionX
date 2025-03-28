/**
 * @file chatlog.h
 *
 * Adds Chat log QoL feature
 */
#pragma once

#include "DiabloUI/ui_flags.hpp"
#include "engine/surface.hpp"
#include "player.h"

namespace devilution {

extern bool ChatLogFlag;

void ToggleChatLog();
void AddMessageToChatLog(std::string_view message, Player *player = nullptr, UiFlags flags = UiFlags::ColorWhite);
void DrawChatLog(const Surface &out);
void ChatLogScrollUp();
void ChatLogScrollDown();
void ChatLogScrollTop();
void ChatLogScrollBottom();

} // namespace devilution
