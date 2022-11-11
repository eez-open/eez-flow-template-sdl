#pragma once

#include <eez/gui/data.h>
#include <eez/gui/widget.h>

namespace eez {
namespace gui {

enum DataEnum {
    DATA_ID_NONE = 0,
    DATA_ID_ALERT_MESSAGE = 1
};

void data_none(DataOperationEnum operation, const WidgetCursor &cursor, Value &value);
void data_alert_message(DataOperationEnum operation, const WidgetCursor &cursor, Value &value);

typedef void (*DataOperationsFunction)(DataOperationEnum operation, const WidgetCursor &widgetCursor, Value &value);

extern DataOperationsFunction g_dataOperationsFunctions[];

enum ActionsEnum {
    ACTION_ID_NONE = 0,
    ACTION_ID_YES = 1,
    ACTION_ID_NO = 2,
    ACTION_ID_CANCEL = 3,
    ACTION_ID_EDIT = 4,
    ACTION_ID_DRAG_OVERLAY = 5,
    ACTION_ID_SCROLL = 6
};

void action_yes();
void action_no();
void action_cancel();
void action_edit();
void action_drag_overlay();
void action_scroll();

extern ActionExecFunc g_actionExecFunctions[];

enum FontsEnum {
    FONT_ID_NONE = 0,
    FONT_ID_SHADOW = 1,
    FONT_ID_MEDIUM = 2
};

enum BitmapsEnum {
    BITMAP_ID_NONE = 0
};

enum StylesEnum {
    STYLE_ID_NONE = 0
};

enum ThemesEnum {
    THEME_ID_DEFAULT = 0
};

enum ColorsEnum {
    COLOR_ID_TRANSPARENT = 65535,
    COLOR_ID_BACKGROUND = 0,
    COLOR_ID_BACKDROP = 1,
    COLOR_ID_TEXT = 2,
    COLOR_ID_TEXT_INACTIVE = 3,
    COLOR_ID_DARK_TEXT = 4,
    COLOR_ID_BORDER = 5,
    COLOR_ID_ACTIVE_BACKGROUND = 6,
    COLOR_ID_BUTTON_TEXT = 7,
    COLOR_ID_BUTTON_BACKGROUND = 8,
    COLOR_ID_BUTTON_ACTIVE_BACKGROUND = 9,
    COLOR_ID_BUTTON_BORDER = 10,
    COLOR_ID_BUTTON_DISABLED_TEXT = 11,
    COLOR_ID_BUTTON_DISABLED_BACKGROUND = 12,
    COLOR_ID_BUTTON_DISABLED_BORDER = 13,
    COLOR_ID_ERROR = 14,
    COLOR_ID_NOTE = 15,
    COLOR_ID_SWITCH_WIDGET_COLOR = 16,
    COLOR_ID_SWITCH_WIDGET_BACKGROUND_ON = 17,
    COLOR_ID_SWITCH_WIDGET_BACKGROUND_OFF = 18,
    COLOR_ID_SWITCH_WIDGET_BORDER = 19,
    COLOR_ID_SLIDER_WIDGET_COLOR = 20,
    COLOR_ID_SLIDER_WIDGET_BACKGROUND = 21,
    COLOR_ID_DROP_DOWN_LIST_COLOR = 22,
    COLOR_ID_DROP_DOWN_LIST_COLOR_DISABLED = 23,
    COLOR_ID_DROP_DOWN_LIST_BACKGROUND = 24,
    COLOR_ID_DROP_DOWN_LIST_BORDER = 25,
    COLOR_ID_DROP_DOWN_LIST_ACTIVE_BACKGROUND = 26,
    COLOR_ID_TEXT_INPUT_COLOR = 27,
    COLOR_ID_TEXT_INPUT_COLOR_DISABLED = 28,
    COLOR_ID_TEXT_INPUT_BACKGROUND = 29,
    COLOR_ID_TEXT_INPUT_ACTIVE_BACKGROUND = 30,
    COLOR_ID_TEXT_INPUT_BORDER = 31,
	COLOR_ID_CUSTOM_UNDEFINED = 32,
	COLOR_ID_CUSTOM_000000 = 33,
	COLOR_ID_CUSTOM_00FF1E = 34
};

enum PagesEnum {
    PAGE_ID_NONE = 0,
    PAGE_ID_MAIN = 1
};

extern const uint8_t assets[8363];

} // namespace gui
} // namespace eez
