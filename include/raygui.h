/*******************************************************************************************
 *
 *   raygui v3.1 - A simple and easy-to-use immediate-mode gui library
 *
 *   DESCRIPTION:
 *
 *   raygui is a tools-dev-focused immediate-mode-gui library based on raylib
 *but also available as a standalone library, as long as input and drawing
 *functions are provided.
 *
 *   Controls provided:
 *
 *   # Container/separators Controls
 *       - WindowBox
 *       - GroupBox
 *       - Line
 *       - Panel
 *       - ScrollPanel
 *
 *   # Basic Controls
 *       - Label
 *       - Button
 *       - LabelButton   --> Label
 *       - Toggle
 *       - ToggleGroup   --> Toggle
 *       - CheckBox
 *       - ComboBox
 *       - DropdownBox
 *       - TextBox
 *       - TextBoxMulti
 *       - ValueBox      --> TextBox
 *       - Spinner       --> Button, ValueBox
 *       - Slider
 *       - SliderBar     --> Slider
 *       - ProgressBar
 *       - StatusBar
 *       - ScrollBar     // TODO: Really? Do we need it? We have
 *GuiScrollPanel()
 *       - DummyRec
 *       - Grid
 *
 *   # Advance Controls
 *       - ListView
 *       - ColorPicker   --> ColorPanel, ColorBarHue
 *       - MessageBox    --> Window, Label, Button
 *       - TextInputBox  --> Window, Label, TextBox, Button
 *
 *   It also provides a set of functions for styling the controls based on its
 *properties (size, color).
 *
 *
 *   RAYGUI STYLE (guiStyle):
 *
 *   raygui uses a global data array for all gui style properties (allocated on
 *data segment by default), when a new style is loaded, it is loaded over the
 *global style... but a default gui style could always be recovered with
 *GuiLoadStyleDefault() function, that overwrites the current style to the
 *default one
 *
 *   The global style array size is fixed and depends on the number of controls
 *and properties:
 *
 *       static unsigned int guiStyle[RAYGUI_MAX_CONTROLS*(RAYGUI_MAX_PROPS_BASE
 *+ RAYGUI_MAX_PROPS_EXTENDED)];
 *
 *   guiStyle size is by default: 16*(16 + 8) = 384*4 = 1536 bytes = 1.5 KB
 *
 *   Note that the first set of BASE properties (by default guiStyle[0..15])
 *belong to the generic style used for all controls, when any of those base
 *values is set, it is automatically populated to all controls, so, specific
 *control values overwriting generic style should be set after base values.
 *
 *   After the first BASE set we have the EXTENDED properties (by default
 *guiStyle[16..23]), those properties are actually common to all controls and
 *can not be overwritten individually (like BASE ones) Some of those properties
 *are: TEXT_SIZE, TEXT_SPACING, LINE_COLOR, BACKGROUND_COLOR
 *
 *   Custom control properties can be defined using the EXTENDED properties for
 *each independent control.
 *
 *   TOOL: rGuiStyler is a visual tool to customize raygui style.
 *
 *
 *   RAYGUI ICONS (guiIcons):
 *
 *   raygui could use a global array containing icons data (allocated on data
 *segment by default), a custom icons set could be loaded over this array using
 *GuiLoadIcons(), but loaded icons set must be same RAYGUI_ICON_SIZE and no more
 *than RAYGUI_ICON_MAX_ICONS will be loaded
 *
 *   Every icon is codified in binary form, using 1 bit per pixel, so, every
 *16x16 icon requires 8 integers (16*16/32) to be stored in memory.
 *
 *   When the icon is draw, actually one quad per pixel is drawn if the bit for
 *that pixel is set.
 *
 *   The global icons array size is fixed and depends on the number of icons and
 *size:
 *
 *       static unsigned int
 *guiIcons[RAYGUI_ICON_MAX_ICONS*RAYGUI_ICON_DATA_ELEMENTS];
 *
 *   guiIcons size is by default: 256*(16*16/32) = 2048*4 = 8192 bytes = 8 KB
 *
 *   TOOL: rGuiIcons is a visual tool to customize raygui icons.
 *
 *
 *   CONFIGURATION:
 *
 *   #define RAYGUI_IMPLEMENTATION
 *       Generates the implementation of the library into the included file.
 *       If not defined, the library is in header only mode and can be included
 *in other headers or source files without problems. But only ONE file should
 *hold the implementation.
 *
 *   #define RAYGUI_STANDALONE
 *       Avoid raylib.h header inclusion in this file. Data types defined on
 *raylib are defined internally in the library and input management and drawing
 *functions must be provided by the user (check library implementation for
 *further details).
 *
 *   #define RAYGUI_NO_ICONS
 *       Avoid including embedded ricons data (256 icons, 16x16 pixels, 1-bit
 *per pixel, 2KB)
 *
 *   #define RAYGUI_CUSTOM_ICONS
 *       Includes custom ricons.h header defining a set of custom icons,
 *       this file can be generated using rGuiIcons tool
 *
 *
 *   VERSIONS HISTORY:
 *       3.1 (12-Jan-2021) REVIEWED: Default style for consistency (aligned with
 *rGuiLayout v2.5 tool) REVIEWED: GuiLoadStyle() to support compressed font
 *atlas image data and unload previous textures REVIEWED: External icons usage
 *logic REVIEWED: GuiLine() for centered alignment when including text RENAMED:
 *Multiple controls properties definitions to prepend RAYGUI_ RENAMED: RICON_
 *references to RAYGUI_ICON_ for library consistency Projects updated and
 *multiple tweaks 3.0 (04-Nov-2021) Integrated ricons data to avoid external
 *file REDESIGNED: GuiTextBoxMulti() REMOVED: GuiImageButton*() Multiple minor
 *tweaks and bugs corrected 2.9 (17-Mar-2021) REMOVED: Tooltip API 2.8
 *(03-May-2020) Centralized rectangles drawing to GuiDrawRectangle() 2.7
 *(20-Feb-2020) ADDED: Possible tooltips API 2.6 (09-Sep-2019) ADDED:
 *GuiTextInputBox() REDESIGNED: GuiListView*(), GuiDropdownBox(), GuiSlider*(),
 *GuiProgressBar(), GuiMessageBox() REVIEWED: GuiTextBox(), GuiSpinner(),
 *GuiValueBox(), GuiLoadStyle() Replaced property INNER_PADDING by TEXT_PADDING,
 *renamed some properties ADDED: 8 new custom styles ready to use Multiple minor
 *tweaks and bugs corrected 2.5 (28-May-2019) Implemented extended GuiTextBox(),
 *GuiValueBox(), GuiSpinner() 2.3 (29-Apr-2019) ADDED: rIcons auxiliar library
 *and support for it, multiple controls reviewed Refactor all controls drawing
 *mechanism to use control state 2.2 (05-Feb-2019) ADDED: GuiScrollBar(),
 *GuiScrollPanel(), reviewed GuiListView(), removed Gui*Ex() controls 2.1
 *(26-Dec-2018) REDESIGNED: GuiCheckBox(), GuiComboBox(), GuiDropdownBox(),
 *GuiToggleGroup() > Use combined text string REDESIGNED: Style system (breaking
 *change) 2.0 (08-Nov-2018) ADDED: Support controls guiLock and custom fonts
 *                         REVIEWED: GuiComboBox(), GuiListView()...
 *       1.9 (09-Oct-2018) REVIEWED: GuiGrid(), GuiTextBox(), GuiTextBoxMulti(),
 *GuiValueBox()... 1.8 (01-May-2018) Lot of rework and redesign to align with
 *rGuiStyler and rGuiLayout 1.5 (21-Jun-2017) Working in an improved styles
 *system 1.4 (15-Jun-2017) Rewritten all GUI functions (removed useless ones)
 *       1.3 (12-Jun-2017) Complete redesign of style system
 *       1.1 (01-Jun-2017) Complete review of the library
 *       1.0 (07-Jun-2016) Converted to header-only by Ramon Santamaria.
 *       0.9 (07-Mar-2016) Reviewed and tested by Albert Martos, Ian Eito,
 *Sergio Martinez and Ramon Santamaria. 0.8 (27-Aug-2015) Initial release.
 *Implemented by Kevin Gato, Daniel Nicolás and Ramon Santamaria.
 *
 *
 *   CONTRIBUTORS:
 *
 *       Ramon Santamaria:   Supervision, review, redesign, update and
 *maintenance Vlad Adrian:        Complete rewrite of GuiTextBox() to support
 *extended features (2019) Sergio Martinez:    Review, testing (2015) and
 *redesign of multiple controls (2018) Adria Arranz:       Testing and
 *Implementation of additional controls (2018) Jordi Jorba:        Testing and
 *Implementation of additional controls (2018) Albert Martos:      Review and
 *testing of the library (2015) Ian Eito:           Review and testing of the
 *library (2015) Kevin Gato:         Initial implementation of basic components
 *(2014) Daniel Nicolas:     Initial implementation of basic components (2014)
 *
 *
 *   LICENSE: zlib/libpng
 *
 *   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
 *
 *   This software is provided "as-is", without any express or implied warranty.
 *In no event will the authors be held liable for any damages arising from the
 *use of this software.
 *
 *   Permission is granted to anyone to use this software for any purpose,
 *including commercial applications, and to alter it and redistribute it freely,
 *subject to the following restrictions:
 *
 *     1. The origin of this software must not be misrepresented; you must not
 *claim that you wrote the original software. If you use this software in a
 *product, an acknowledgment in the product documentation would be appreciated
 *but is not required.
 *
 *     2. Altered source versions must be plainly marked as such, and must not
 *be misrepresented as being the original software.
 *
 *     3. This notice may not be removed or altered from any source
 *distribution.
 *
 **********************************************************************************************/

#ifndef RAYGUI_H
#define RAYGUI_H

#define RAYGUI_VERSION "3.1"

#if !defined(RAYGUI_STANDALONE)
#include "raylib.h"
#endif

// Function specifiers in case library is build/used as a shared library
// (Windows) NOTE: Microsoft specifiers to tell compiler that symbols are
// imported/exported from a .dll
#if defined(_WIN32)
#if defined(BUILD_LIBTYPE_SHARED)
#define RAYGUIAPI \
  __declspec(dllexport)  // We are building the library as a Win32 shared
                         // library (.dll)
#elif defined(USE_LIBTYPE_SHARED)
#define RAYGUIAPI \
  __declspec(     \
      dllimport)  // We are using the library as a Win32 shared library (.dll)
#endif
#endif

// Function specifiers definition
#ifndef RAYGUIAPI
#define RAYGUIAPI  // Functions defined as 'extern' by default (implicit
                   // specifiers)
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
// Allow custom memory allocators
#ifndef RAYGUI_MALLOC
#define RAYGUI_MALLOC(sz) malloc(sz)
#endif
#ifndef RAYGUI_CALLOC
#define RAYGUI_CALLOC(n, sz) calloc(n, sz)
#endif
#ifndef RAYGUI_FREE
#define RAYGUI_FREE(p) free(p)
#endif

// Simple log system to avoid printf() calls if required
// NOTE: Avoiding those calls, also avoids const strings memory usage
#define RAYGUI_SUPPORT_LOG_INFO
#if defined(RAYGUI_SUPPORT_LOG_INFO)
#define RAYGUI_LOG(...) printf(__VA_ARGS__)
#else
#define RAYGUI_LOG(...)
#endif

// Style property
typedef struct GuiStyleProp {
  unsigned short controlId;
  unsigned short propertyId;
  int propertyValue;
} GuiStyleProp;

// Gui control state
typedef enum {
  GUI_STATE_NORMAL = 0,
  GUI_STATE_FOCUSED,
  GUI_STATE_PRESSED,
  GUI_STATE_DISABLED,
} GuiControlState;

// Gui control text alignment
typedef enum {
  GUI_TEXT_ALIGN_LEFT = 0,
  GUI_TEXT_ALIGN_CENTER,
  GUI_TEXT_ALIGN_RIGHT,
} GuiTextAlignment;

// Gui controls
typedef enum {
  DEFAULT = 0,  // Generic control -> populates to all controls when set
  LABEL,        // Used also for: LABELBUTTON
  BUTTON,
  TOGGLE,  // Used also for: TOGGLEGROUP
  SLIDER,  // Used also for: SLIDERBAR
  PROGRESSBAR,
  CHECKBOX,
  COMBOBOX,
  DROPDOWNBOX,
  TEXTBOX,  // Used also for: TEXTBOXMULTI
  VALUEBOX,
  SPINNER,
  LISTVIEW,
  COLORPICKER,
  SCROLLBAR,
  STATUSBAR
} GuiControl;

// Gui base properties for every control
// NOTE: RAYGUI_MAX_PROPS_BASE properties (by default 16 properties)
typedef enum {
  BORDER_COLOR_NORMAL = 0,
  BASE_COLOR_NORMAL,
  TEXT_COLOR_NORMAL,
  BORDER_COLOR_FOCUSED,
  BASE_COLOR_FOCUSED,
  TEXT_COLOR_FOCUSED,
  BORDER_COLOR_PRESSED,
  BASE_COLOR_PRESSED,
  TEXT_COLOR_PRESSED,
  BORDER_COLOR_DISABLED,
  BASE_COLOR_DISABLED,
  TEXT_COLOR_DISABLED,
  BORDER_WIDTH,
  TEXT_PADDING,
  TEXT_ALIGNMENT,
  RESERVED
} GuiControlProperty;

// Gui extended properties depend on control
// NOTE: RAYGUI_MAX_PROPS_EXTENDED properties (by default 8 properties)

// DEFAULT extended properties
// NOTE: Those properties are actually common to all controls
typedef enum {
  TEXT_SIZE = 16,
  TEXT_SPACING,
  LINE_COLOR,
  BACKGROUND_COLOR,
} GuiDefaultProperty;

// Label
// typedef enum { } GuiLabelProperty;

// Button
// typedef enum { } GuiButtonProperty;

// Toggle/ToggleGroup
typedef enum {
  GROUP_PADDING = 16,
} GuiToggleProperty;

// Slider/SliderBar
typedef enum { SLIDER_WIDTH = 16, SLIDER_PADDING } GuiSliderProperty;

// ProgressBar
typedef enum {
  PROGRESS_PADDING = 16,
} GuiProgressBarProperty;

// CheckBox
typedef enum { CHECK_PADDING = 16 } GuiCheckBoxProperty;

// ComboBox
typedef enum {
  COMBO_BUTTON_WIDTH = 16,
  COMBO_BUTTON_PADDING
} GuiComboBoxProperty;

// DropdownBox
typedef enum {
  ARROW_PADDING = 16,
  DROPDOWN_ITEMS_PADDING
} GuiDropdownBoxProperty;

// TextBox/TextBoxMulti/ValueBox/Spinner
typedef enum {
  TEXT_INNER_PADDING = 16,
  TEXT_LINES_PADDING,
  COLOR_SELECTED_FG,
  COLOR_SELECTED_BG
} GuiTextBoxProperty;

// Spinner
typedef enum {
  SPIN_BUTTON_WIDTH = 16,
  SPIN_BUTTON_PADDING,
} GuiSpinnerProperty;

// ScrollBar
typedef enum {
  ARROWS_SIZE = 16,
  ARROWS_VISIBLE,
  SCROLL_SLIDER_PADDING,
  SCROLL_SLIDER_SIZE,
  SCROLL_PADDING,
  SCROLL_SPEED,
} GuiScrollBarProperty;

// ScrollBar side
typedef enum { SCROLLBAR_LEFT_SIDE = 0, SCROLLBAR_RIGHT_SIDE } GuiScrollBarSide;

// ListView
typedef enum {
  LIST_ITEMS_HEIGHT = 16,
  LIST_ITEMS_PADDING,
  SCROLLBAR_WIDTH,
  SCROLLBAR_SIDE,
} GuiListViewProperty;

// ColorPicker
typedef enum {
  COLOR_SELECTOR_SIZE = 16,
  HUEBAR_WIDTH,             // Right hue bar width
  HUEBAR_PADDING,           // Right hue bar separation from panel
  HUEBAR_SELECTOR_HEIGHT,   // Right hue bar selector height
  HUEBAR_SELECTOR_OVERFLOW  // Right hue bar selector overflow
} GuiColorPickerProperty;

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C" {  // Prevents name mangling of functions
#endif

// Embedded raygui icons, no external file provided
#define RAYGUI_ICON_SIZE 16             // Size of icons (squared)
#define RAYGUI_ICON_MAX_ICONS 256       // Maximum number of icons
#define RAYGUI_ICON_MAX_NAME_LENGTH 32  // Maximum length of icon name id

// Icons data is defined by bit array (every bit represents one pixel)
// Those arrays are stored as unsigned int data arrays, so every array
// element defines 32 pixels (bits) of information
// Number of elemens depend on RAYGUI_ICON_SIZE (by default 16x16 pixels)
#define RAYGUI_ICON_DATA_ELEMENTS (RAYGUI_ICON_SIZE * RAYGUI_ICON_SIZE / 32)

//----------------------------------------------------------------------------------
// Icons enumeration
//----------------------------------------------------------------------------------
typedef enum {
  RAYGUI_ICON_NONE = 0,
  RAYGUI_ICON_FOLDER_FILE_OPEN = 1,
  RAYGUI_ICON_FILE_SAVE_CLASSIC = 2,
  RAYGUI_ICON_FOLDER_OPEN = 3,
  RAYGUI_ICON_FOLDER_SAVE = 4,
  RAYGUI_ICON_FILE_OPEN = 5,
  RAYGUI_ICON_FILE_SAVE = 6,
  RAYGUI_ICON_FILE_EXPORT = 7,
  RAYGUI_ICON_FILE_NEW = 8,
  RAYGUI_ICON_FILE_DELETE = 9,
  RAYGUI_ICON_FILETYPE_TEXT = 10,
  RAYGUI_ICON_FILETYPE_AUDIO = 11,
  RAYGUI_ICON_FILETYPE_IMAGE = 12,
  RAYGUI_ICON_FILETYPE_PLAY = 13,
  RAYGUI_ICON_FILETYPE_VIDEO = 14,
  RAYGUI_ICON_FILETYPE_INFO = 15,
  RAYGUI_ICON_FILE_COPY = 16,
  RAYGUI_ICON_FILE_CUT = 17,
  RAYGUI_ICON_FILE_PASTE = 18,
  RAYGUI_ICON_CURSOR_HAND = 19,
  RAYGUI_ICON_CURSOR_POINTER = 20,
  RAYGUI_ICON_CURSOR_CLASSIC = 21,
  RAYGUI_ICON_PENCIL = 22,
  RAYGUI_ICON_PENCIL_BIG = 23,
  RAYGUI_ICON_BRUSH_CLASSIC = 24,
  RAYGUI_ICON_BRUSH_PAINTER = 25,
  RAYGUI_ICON_WATER_DROP = 26,
  RAYGUI_ICON_COLOR_PICKER = 27,
  RAYGUI_ICON_RUBBER = 28,
  RAYGUI_ICON_COLOR_BUCKET = 29,
  RAYGUI_ICON_TEXT_T = 30,
  RAYGUI_ICON_TEXT_A = 31,
  RAYGUI_ICON_SCALE = 32,
  RAYGUI_ICON_RESIZE = 33,
  RAYGUI_ICON_FILTER_POINT = 34,
  RAYGUI_ICON_FILTER_BILINEAR = 35,
  RAYGUI_ICON_CROP = 36,
  RAYGUI_ICON_CROP_ALPHA = 37,
  RAYGUI_ICON_SQUARE_TOGGLE = 38,
  RAYGUI_ICON_SYMMETRY = 39,
  RAYGUI_ICON_SYMMETRY_HORIZONTAL = 40,
  RAYGUI_ICON_SYMMETRY_VERTICAL = 41,
  RAYGUI_ICON_LENS = 42,
  RAYGUI_ICON_LENS_BIG = 43,
  RAYGUI_ICON_EYE_ON = 44,
  RAYGUI_ICON_EYE_OFF = 45,
  RAYGUI_ICON_FILTER_TOP = 46,
  RAYGUI_ICON_FILTER = 47,
  RAYGUI_ICON_TARGET_POINT = 48,
  RAYGUI_ICON_TARGET_SMALL = 49,
  RAYGUI_ICON_TARGET_BIG = 50,
  RAYGUI_ICON_TARGET_MOVE = 51,
  RAYGUI_ICON_CURSOR_MOVE = 52,
  RAYGUI_ICON_CURSOR_SCALE = 53,
  RAYGUI_ICON_CURSOR_SCALE_RIGHT = 54,
  RAYGUI_ICON_CURSOR_SCALE_LEFT = 55,
  RAYGUI_ICON_UNDO = 56,
  RAYGUI_ICON_REDO = 57,
  RAYGUI_ICON_REREDO = 58,
  RAYGUI_ICON_MUTATE = 59,
  RAYGUI_ICON_ROTATE = 60,
  RAYGUI_ICON_REPEAT = 61,
  RAYGUI_ICON_SHUFFLE = 62,
  RAYGUI_ICON_EMPTYBOX = 63,
  RAYGUI_ICON_TARGET = 64,
  RAYGUI_ICON_TARGET_SMALL_FILL = 65,
  RAYGUI_ICON_TARGET_BIG_FILL = 66,
  RAYGUI_ICON_TARGET_MOVE_FILL = 67,
  RAYGUI_ICON_CURSOR_MOVE_FILL = 68,
  RAYGUI_ICON_CURSOR_SCALE_FILL = 69,
  RAYGUI_ICON_CURSOR_SCALE_RIGHT_FILL = 70,
  RAYGUI_ICON_CURSOR_SCALE_LEFT_FILL = 71,
  RAYGUI_ICON_UNDO_FILL = 72,
  RAYGUI_ICON_REDO_FILL = 73,
  RAYGUI_ICON_REREDO_FILL = 74,
  RAYGUI_ICON_MUTATE_FILL = 75,
  RAYGUI_ICON_ROTATE_FILL = 76,
  RAYGUI_ICON_REPEAT_FILL = 77,
  RAYGUI_ICON_SHUFFLE_FILL = 78,
  RAYGUI_ICON_EMPTYBOX_SMALL = 79,
  RAYGUI_ICON_BOX = 80,
  RAYGUI_ICON_BOX_TOP = 81,
  RAYGUI_ICON_BOX_TOP_RIGHT = 82,
  RAYGUI_ICON_BOX_RIGHT = 83,
  RAYGUI_ICON_BOX_BOTTOM_RIGHT = 84,
  RAYGUI_ICON_BOX_BOTTOM = 85,
  RAYGUI_ICON_BOX_BOTTOM_LEFT = 86,
  RAYGUI_ICON_BOX_LEFT = 87,
  RAYGUI_ICON_BOX_TOP_LEFT = 88,
  RAYGUI_ICON_BOX_CENTER = 89,
  RAYGUI_ICON_BOX_CIRCLE_MASK = 90,
  RAYGUI_ICON_POT = 91,
  RAYGUI_ICON_ALPHA_MULTIPLY = 92,
  RAYGUI_ICON_ALPHA_CLEAR = 93,
  RAYGUI_ICON_DITHERING = 94,
  RAYGUI_ICON_MIPMAPS = 95,
  RAYGUI_ICON_BOX_GRID = 96,
  RAYGUI_ICON_GRID = 97,
  RAYGUI_ICON_BOX_CORNERS_SMALL = 98,
  RAYGUI_ICON_BOX_CORNERS_BIG = 99,
  RAYGUI_ICON_FOUR_BOXES = 100,
  RAYGUI_ICON_GRID_FILL = 101,
  RAYGUI_ICON_BOX_MULTISIZE = 102,
  RAYGUI_ICON_ZOOM_SMALL = 103,
  RAYGUI_ICON_ZOOM_MEDIUM = 104,
  RAYGUI_ICON_ZOOM_BIG = 105,
  RAYGUI_ICON_ZOOM_ALL = 106,
  RAYGUI_ICON_ZOOM_CENTER = 107,
  RAYGUI_ICON_BOX_DOTS_SMALL = 108,
  RAYGUI_ICON_BOX_DOTS_BIG = 109,
  RAYGUI_ICON_BOX_CONCENTRIC = 110,
  RAYGUI_ICON_BOX_GRID_BIG = 111,
  RAYGUI_ICON_OK_TICK = 112,
  RAYGUI_ICON_CROSS = 113,
  RAYGUI_ICON_ARROW_LEFT = 114,
  RAYGUI_ICON_ARROW_RIGHT = 115,
  RAYGUI_ICON_ARROW_DOWN = 116,
  RAYGUI_ICON_ARROW_UP = 117,
  RAYGUI_ICON_ARROW_LEFT_FILL = 118,
  RAYGUI_ICON_ARROW_RIGHT_FILL = 119,
  RAYGUI_ICON_ARROW_DOWN_FILL = 120,
  RAYGUI_ICON_ARROW_UP_FILL = 121,
  RAYGUI_ICON_AUDIO = 122,
  RAYGUI_ICON_FX = 123,
  RAYGUI_ICON_WAVE = 124,
  RAYGUI_ICON_WAVE_SINUS = 125,
  RAYGUI_ICON_WAVE_SQUARE = 126,
  RAYGUI_ICON_WAVE_TRIANGULAR = 127,
  RAYGUI_ICON_CROSS_SMALL = 128,
  RAYGUI_ICON_PLAYER_PREVIOUS = 129,
  RAYGUI_ICON_PLAYER_PLAY_BACK = 130,
  RAYGUI_ICON_PLAYER_PLAY = 131,
  RAYGUI_ICON_PLAYER_PAUSE = 132,
  RAYGUI_ICON_PLAYER_STOP = 133,
  RAYGUI_ICON_PLAYER_NEXT = 134,
  RAYGUI_ICON_PLAYER_RECORD = 135,
  RAYGUI_ICON_MAGNET = 136,
  RAYGUI_ICON_LOCK_CLOSE = 137,
  RAYGUI_ICON_LOCK_OPEN = 138,
  RAYGUI_ICON_CLOCK = 139,
  RAYGUI_ICON_TOOLS = 140,
  RAYGUI_ICON_GEAR = 141,
  RAYGUI_ICON_GEAR_BIG = 142,
  RAYGUI_ICON_BIN = 143,
  RAYGUI_ICON_HAND_POINTER = 144,
  RAYGUI_ICON_LASER = 145,
  RAYGUI_ICON_COIN = 146,
  RAYGUI_ICON_EXPLOSION = 147,
  RAYGUI_ICON_1UP = 148,
  RAYGUI_ICON_PLAYER = 149,
  RAYGUI_ICON_PLAYER_JUMP = 150,
  RAYGUI_ICON_KEY = 151,
  RAYGUI_ICON_DEMON = 152,
  RAYGUI_ICON_TEXT_POPUP = 153,
  RAYGUI_ICON_GEAR_EX = 154,
  RAYGUI_ICON_CRACK = 155,
  RAYGUI_ICON_CRACK_POINTS = 156,
  RAYGUI_ICON_STAR = 157,
  RAYGUI_ICON_DOOR = 158,
  RAYGUI_ICON_EXIT = 159,
  RAYGUI_ICON_MODE_2D = 160,
  RAYGUI_ICON_MODE_3D = 161,
  RAYGUI_ICON_CUBE = 162,
  RAYGUI_ICON_CUBE_FACE_TOP = 163,
  RAYGUI_ICON_CUBE_FACE_LEFT = 164,
  RAYGUI_ICON_CUBE_FACE_FRONT = 165,
  RAYGUI_ICON_CUBE_FACE_BOTTOM = 166,
  RAYGUI_ICON_CUBE_FACE_RIGHT = 167,
  RAYGUI_ICON_CUBE_FACE_BACK = 168,
  RAYGUI_ICON_CAMERA = 169,
  RAYGUI_ICON_SPECIAL = 170,
  RAYGUI_ICON_LINK_NET = 171,
  RAYGUI_ICON_LINK_BOXES = 172,
  RAYGUI_ICON_LINK_MULTI = 173,
  RAYGUI_ICON_LINK = 174,
  RAYGUI_ICON_LINK_BROKE = 175,
  RAYGUI_ICON_TEXT_NOTES = 176,
  RAYGUI_ICON_NOTEBOOK = 177,
  RAYGUI_ICON_SUITCASE = 178,
  RAYGUI_ICON_SUITCASE_ZIP = 179,
  RAYGUI_ICON_MAILBOX = 180,
  RAYGUI_ICON_MONITOR = 181,
  RAYGUI_ICON_PRINTER = 182,
  RAYGUI_ICON_PHOTO_CAMERA = 183,
  RAYGUI_ICON_PHOTO_CAMERA_FLASH = 184,
  RAYGUI_ICON_HOUSE = 185,
  RAYGUI_ICON_HEART = 186,
  RAYGUI_ICON_CORNER = 187,
  RAYGUI_ICON_VERTICAL_BARS = 188,
  RAYGUI_ICON_VERTICAL_BARS_FILL = 189,
  RAYGUI_ICON_LIFE_BARS = 190,
  RAYGUI_ICON_INFO = 191,
  RAYGUI_ICON_CROSSLINE = 192,
  RAYGUI_ICON_HELP = 193,
  RAYGUI_ICON_FILETYPE_ALPHA = 194,
  RAYGUI_ICON_FILETYPE_HOME = 195,
  RAYGUI_ICON_LAYERS_VISIBLE = 196,
  RAYGUI_ICON_LAYERS = 197,
  RAYGUI_ICON_WINDOW = 198,
  RAYGUI_ICON_HIDPI = 199,
  RAYGUI_ICON_PLUS = 200,
  RAYGUI_ICON_MINUS = 201,
  RAYGUI_ICON_202 = 202,
  RAYGUI_ICON_203 = 203,
  RAYGUI_ICON_204 = 204,
  RAYGUI_ICON_205 = 205,
  RAYGUI_ICON_206 = 206,
  RAYGUI_ICON_207 = 207,
  RAYGUI_ICON_208 = 208,
  RAYGUI_ICON_209 = 209,
  RAYGUI_ICON_210 = 210,
  RAYGUI_ICON_211 = 211,
  RAYGUI_ICON_212 = 212,
  RAYGUI_ICON_213 = 213,
  RAYGUI_ICON_214 = 214,
  RAYGUI_ICON_215 = 215,
  RAYGUI_ICON_216 = 216,
  RAYGUI_ICON_217 = 217,
  RAYGUI_ICON_218 = 218,
  RAYGUI_ICON_219 = 219,
  RAYGUI_ICON_220 = 220,
  RAYGUI_ICON_221 = 221,
  RAYGUI_ICON_222 = 222,
  RAYGUI_ICON_223 = 223,
  RAYGUI_ICON_224 = 224,
  RAYGUI_ICON_225 = 225,
  RAYGUI_ICON_226 = 226,
  RAYGUI_ICON_227 = 227,
  RAYGUI_ICON_228 = 228,
  RAYGUI_ICON_229 = 229,
  RAYGUI_ICON_230 = 230,
  RAYGUI_ICON_231 = 231,
  RAYGUI_ICON_232 = 232,
  RAYGUI_ICON_233 = 233,
  RAYGUI_ICON_234 = 234,
  RAYGUI_ICON_235 = 235,
  RAYGUI_ICON_236 = 236,
  RAYGUI_ICON_237 = 237,
  RAYGUI_ICON_238 = 238,
  RAYGUI_ICON_239 = 239,
  RAYGUI_ICON_240 = 240,
  RAYGUI_ICON_241 = 241,
  RAYGUI_ICON_242 = 242,
  RAYGUI_ICON_243 = 243,
  RAYGUI_ICON_244 = 244,
  RAYGUI_ICON_245 = 245,
  RAYGUI_ICON_246 = 246,
  RAYGUI_ICON_247 = 247,
  RAYGUI_ICON_248 = 248,
  RAYGUI_ICON_249 = 249,
  RAYGUI_ICON_250 = 250,
  RAYGUI_ICON_251 = 251,
  RAYGUI_ICON_252 = 252,
  RAYGUI_ICON_253 = 253,
  RAYGUI_ICON_254 = 254,
  RAYGUI_ICON_255 = 255,
} guiIconName;

//----------------------------------------------------------------------------------
// Icons data for all gui possible icons (allocated on data segment by default)
//
// NOTE 1: Every icon is codified in binary form, using 1 bit per pixel, so,
// every 16x16 icon requires 8 integers (16*16/32) to be stored
//
// NOTE 2: A different icon set could be loaded over this array using
// GuiLoadIcons(), but loaded icons set must be same RAYGUI_ICON_SIZE and no
// more than RAYGUI_ICON_MAX_ICONS
//
// guiIcons size is by default: 256*(16*16/32) = 2048*4 = 8192 bytes = 8 KB
//----------------------------------------------------------------------------------
static unsigned int
    guiIcons[RAYGUI_ICON_MAX_ICONS * RAYGUI_ICON_DATA_ELEMENTS] = {
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_NONE
        0x3ff80000, 0x2f082008, 0x2042207e, 0x40027fc2, 0x40024002,
        0x40024002, 0x40024002, 0x00007ffe,  // RAYGUI_ICON_FOLDER_FILE_OPEN
        0x3ffe0000, 0x44226422, 0x400247e2, 0x5ffa4002, 0x57ea500a,
        0x500a500a, 0x40025ffa, 0x00007ffe,  // RAYGUI_ICON_FILE_SAVE_CLASSIC
        0x00000000, 0x0042007e, 0x40027fc2, 0x40024002, 0x41024002,
        0x44424282, 0x793e4102, 0x00000100,  // RAYGUI_ICON_FOLDER_OPEN
        0x00000000, 0x0042007e, 0x40027fc2, 0x40024002, 0x41024102,
        0x44424102, 0x793e4282, 0x00000000,  // RAYGUI_ICON_FOLDER_SAVE
        0x3ff00000, 0x201c2010, 0x20042004, 0x21042004, 0x24442284,
        0x21042104, 0x20042104, 0x00003ffc,  // RAYGUI_ICON_FILE_OPEN
        0x3ff00000, 0x201c2010, 0x20042004, 0x21042004, 0x21042104,
        0x22842444, 0x20042104, 0x00003ffc,  // RAYGUI_ICON_FILE_SAVE
        0x3ff00000, 0x201c2010, 0x00042004, 0x20041004, 0x20844784,
        0x00841384, 0x20042784, 0x00003ffc,  // RAYGUI_ICON_FILE_EXPORT
        0x3ff00000, 0x201c2010, 0x20042004, 0x20042004, 0x22042204,
        0x22042f84, 0x20042204, 0x00003ffc,  // RAYGUI_ICON_FILE_NEW
        0x3ff00000, 0x201c2010, 0x20042004, 0x20042004, 0x25042884,
        0x25042204, 0x20042884, 0x00003ffc,  // RAYGUI_ICON_FILE_DELETE
        0x3ff00000, 0x201c2010, 0x20042004, 0x20042ff4, 0x20042ff4,
        0x20042ff4, 0x20042004, 0x00003ffc,  // RAYGUI_ICON_FILETYPE_TEXT
        0x3ff00000, 0x201c2010, 0x27042004, 0x244424c4, 0x26442444,
        0x20642664, 0x20042004, 0x00003ffc,  // RAYGUI_ICON_FILETYPE_AUDIO
        0x3ff00000, 0x201c2010, 0x26042604, 0x20042004, 0x35442884,
        0x2414222c, 0x20042004, 0x00003ffc,  // RAYGUI_ICON_FILETYPE_IMAGE
        0x3ff00000, 0x201c2010, 0x20c42004, 0x22442144, 0x22442444,
        0x20c42144, 0x20042004, 0x00003ffc,  // RAYGUI_ICON_FILETYPE_PLAY
        0x3ff00000, 0x3ffc2ff0, 0x3f3c2ff4, 0x3dbc2eb4, 0x3dbc2bb4,
        0x3f3c2eb4, 0x3ffc2ff4, 0x00002ff4,  // RAYGUI_ICON_FILETYPE_VIDEO
        0x3ff00000, 0x201c2010, 0x21842184, 0x21842004, 0x21842184,
        0x21842184, 0x20042184, 0x00003ffc,  // RAYGUI_ICON_FILETYPE_INFO
        0x0ff00000, 0x381c0810, 0x28042804, 0x28042804, 0x28042804,
        0x28042804, 0x20102ffc, 0x00003ff0,  // RAYGUI_ICON_FILE_COPY
        0x00000000, 0x701c0000, 0x079c1e14, 0x55a000f0, 0x079c00f0,
        0x701c1e14, 0x00000000, 0x00000000,  // RAYGUI_ICON_FILE_CUT
        0x01c00000, 0x13e41bec, 0x3f841004, 0x204420c4, 0x20442044,
        0x20442044, 0x207c2044, 0x00003fc0,  // RAYGUI_ICON_FILE_PASTE
        0x00000000, 0x3aa00fe0, 0x2abc2aa0, 0x2aa42aa4, 0x20042aa4,
        0x20042004, 0x3ffc2004, 0x00000000,  // RAYGUI_ICON_CURSOR_HAND
        0x00000000, 0x003c000c, 0x030800c8, 0x30100c10, 0x10202020,
        0x04400840, 0x01800280, 0x00000000,  // RAYGUI_ICON_CURSOR_POINTER
        0x00000000, 0x00180000, 0x01f00078, 0x03e007f0, 0x07c003e0,
        0x04000e40, 0x00000000, 0x00000000,  // RAYGUI_ICON_CURSOR_CLASSIC
        0x00000000, 0x04000000, 0x11000a00, 0x04400a80, 0x01100220,
        0x00580088, 0x00000038, 0x00000000,  // RAYGUI_ICON_PENCIL
        0x04000000, 0x15000a00, 0x50402880, 0x14102820, 0x05040a08,
        0x015c028c, 0x007c00bc, 0x00000000,  // RAYGUI_ICON_PENCIL_BIG
        0x01c00000, 0x01400140, 0x01400140, 0x0ff80140, 0x0ff80808,
        0x0aa80808, 0x0aa80aa8, 0x00000ff8,  // RAYGUI_ICON_BRUSH_CLASSIC
        0x1ffc0000, 0x5ffc7ffe, 0x40004000, 0x00807f80, 0x01c001c0,
        0x01c001c0, 0x01c001c0, 0x00000080,  // RAYGUI_ICON_BRUSH_PAINTER
        0x00000000, 0x00800000, 0x01c00080, 0x03e001c0, 0x07f003e0,
        0x036006f0, 0x000001c0, 0x00000000,  // RAYGUI_ICON_WATER_DROP
        0x00000000, 0x3e003800, 0x1f803f80, 0x0c201e40, 0x02080c10,
        0x00840104, 0x00380044, 0x00000000,  // RAYGUI_ICON_COLOR_PICKER
        0x00000000, 0x07800300, 0x1fe00fc0, 0x3f883fd0, 0x0e021f04,
        0x02040402, 0x00f00108, 0x00000000,  // RAYGUI_ICON_RUBBER
        0x00c00000, 0x02800140, 0x08200440, 0x20081010, 0x2ffe3004,
        0x03f807fc, 0x00e001f0, 0x00000040,  // RAYGUI_ICON_COLOR_BUCKET
        0x00000000, 0x21843ffc, 0x01800180, 0x01800180, 0x01800180,
        0x01800180, 0x03c00180, 0x00000000,  // RAYGUI_ICON_TEXT_T
        0x00800000, 0x01400180, 0x06200340, 0x0c100620, 0x1ff80c10,
        0x380c1808, 0x70067004, 0x0000f80f,  // RAYGUI_ICON_TEXT_A
        0x78000000, 0x50004000, 0x00004800, 0x03c003c0, 0x03c003c0,
        0x00100000, 0x0002000a, 0x0000000e,  // RAYGUI_ICON_SCALE
        0x75560000, 0x5e004002, 0x54001002, 0x41001202, 0x408200fe,
        0x40820082, 0x40820082, 0x00006afe,  // RAYGUI_ICON_RESIZE
        0x00000000, 0x3f003f00, 0x3f003f00, 0x3f003f00, 0x00400080,
        0x001c0020, 0x001c001c, 0x00000000,  // RAYGUI_ICON_FILTER_POINT
        0x6d800000, 0x00004080, 0x40804080, 0x40800000, 0x00406d80,
        0x001c0020, 0x001c001c, 0x00000000,  // RAYGUI_ICON_FILTER_BILINEAR
        0x40080000, 0x1ffe2008, 0x14081008, 0x11081208, 0x10481088,
        0x10081028, 0x10047ff8, 0x00001002,  // RAYGUI_ICON_CROP
        0x00100000, 0x3ffc0010, 0x2ab03550, 0x22b02550, 0x20b02150,
        0x20302050, 0x2000fff0, 0x00002000,  // RAYGUI_ICON_CROP_ALPHA
        0x40000000, 0x1ff82000, 0x04082808, 0x01082208, 0x00482088,
        0x00182028, 0x35542008, 0x00000002,  // RAYGUI_ICON_SQUARE_TOGGLE
        0x00000000, 0x02800280, 0x06c006c0, 0x0ea00ee0, 0x1e901eb0,
        0x3e883e98, 0x7efc7e8c, 0x00000000,  // RAYGUI_ICON_SIMMETRY
        0x01000000, 0x05600100, 0x1d480d50, 0x7d423d44, 0x3d447d42,
        0x0d501d48, 0x01000560, 0x00000100,  // RAYGUI_ICON_SIMMETRY_HORIZONTAL
        0x01800000, 0x04200240, 0x10080810, 0x00001ff8, 0x00007ffe,
        0x0ff01ff8, 0x03c007e0, 0x00000180,  // RAYGUI_ICON_SIMMETRY_VERTICAL
        0x00000000, 0x010800f0, 0x02040204, 0x02040204, 0x07f00308,
        0x1c000e00, 0x30003800, 0x00000000,  // RAYGUI_ICON_LENS
        0x00000000, 0x061803f0, 0x08240c0c, 0x08040814, 0x0c0c0804,
        0x23f01618, 0x18002400, 0x00000000,  // RAYGUI_ICON_LENS_BIG
        0x00000000, 0x00000000, 0x1c7007c0, 0x638e3398, 0x1c703398,
        0x000007c0, 0x00000000, 0x00000000,  // RAYGUI_ICON_EYE_ON
        0x00000000, 0x10002000, 0x04700fc0, 0x610e3218, 0x1c703098,
        0x001007a0, 0x00000008, 0x00000000,  // RAYGUI_ICON_EYE_OFF
        0x00000000, 0x00007ffc, 0x40047ffc, 0x10102008, 0x04400820,
        0x02800280, 0x02800280, 0x00000100,  // RAYGUI_ICON_FILTER_TOP
        0x00000000, 0x40027ffe, 0x10082004, 0x04200810, 0x02400240,
        0x02400240, 0x01400240, 0x000000c0,  // RAYGUI_ICON_FILTER
        0x00800000, 0x00800080, 0x00000080, 0x3c9e0000, 0x00000000,
        0x00800080, 0x00800080, 0x00000000,  // RAYGUI_ICON_TARGET_POINT
        0x00800000, 0x00800080, 0x00800080, 0x3f7e01c0, 0x008001c0,
        0x00800080, 0x00800080, 0x00000000,  // RAYGUI_ICON_TARGET_SMALL
        0x00800000, 0x00800080, 0x03e00080, 0x3e3e0220, 0x03e00220,
        0x00800080, 0x00800080, 0x00000000,  // RAYGUI_ICON_TARGET_BIG
        0x01000000, 0x04400280, 0x01000100, 0x43842008, 0x43849ab2,
        0x01002008, 0x04400100, 0x01000280,  // RAYGUI_ICON_TARGET_MOVE
        0x01000000, 0x04400280, 0x01000100, 0x41042108, 0x41049ff2,
        0x01002108, 0x04400100, 0x01000280,  // RAYGUI_ICON_CURSOR_MOVE
        0x781e0000, 0x500a4002, 0x04204812, 0x00000240, 0x02400000,
        0x48120420, 0x4002500a, 0x0000781e,  // RAYGUI_ICON_CURSOR_SCALE
        0x00000000, 0x20003c00, 0x24002800, 0x01000200, 0x00400080,
        0x00140024, 0x003c0004, 0x00000000,  // RAYGUI_ICON_CURSOR_SCALE_RIGHT
        0x00000000, 0x0004003c, 0x00240014, 0x00800040, 0x02000100,
        0x28002400, 0x3c002000, 0x00000000,  // RAYGUI_ICON_CURSOR_SCALE_LEFT
        0x00000000, 0x00100020, 0x10101fc8, 0x10001020, 0x10001000,
        0x10001000, 0x00001fc0, 0x00000000,  // RAYGUI_ICON_UNDO
        0x00000000, 0x08000400, 0x080813f8, 0x00080408, 0x00080008,
        0x00080008, 0x000003f8, 0x00000000,  // RAYGUI_ICON_REDO
        0x00000000, 0x3ffc0000, 0x20042004, 0x20002000, 0x20402000,
        0x3f902020, 0x00400020, 0x00000000,  // RAYGUI_ICON_REREDO
        0x00000000, 0x3ffc0000, 0x20042004, 0x27fc2004, 0x20202000,
        0x3fc82010, 0x00200010, 0x00000000,  // RAYGUI_ICON_MUTATE
        0x00000000, 0x0ff00000, 0x10081818, 0x11801008, 0x10001180,
        0x18101020, 0x00100fc8, 0x00000020,  // RAYGUI_ICON_ROTATE
        0x00000000, 0x04000200, 0x240429fc, 0x20042204, 0x20442004,
        0x3f942024, 0x00400020, 0x00000000,  // RAYGUI_ICON_REPEAT
        0x00000000, 0x20001000, 0x22104c0e, 0x00801120, 0x11200040,
        0x4c0e2210, 0x10002000, 0x00000000,  // RAYGUI_ICON_SHUFFLE
        0x7ffe0000, 0x50024002, 0x44024802, 0x41024202, 0x40424082,
        0x40124022, 0x4002400a, 0x00007ffe,  // RAYGUI_ICON_EMPTYBOX
        0x00800000, 0x03e00080, 0x08080490, 0x3c9e0808, 0x08080808,
        0x03e00490, 0x00800080, 0x00000000,  // RAYGUI_ICON_TARGET
        0x00800000, 0x00800080, 0x00800080, 0x3ffe01c0, 0x008001c0,
        0x00800080, 0x00800080, 0x00000000,  // RAYGUI_ICON_TARGET_SMALL_FILL
        0x00800000, 0x00800080, 0x03e00080, 0x3ffe03e0, 0x03e003e0,
        0x00800080, 0x00800080, 0x00000000,  // RAYGUI_ICON_TARGET_BIG_FILL
        0x01000000, 0x07c00380, 0x01000100, 0x638c2008, 0x638cfbbe,
        0x01002008, 0x07c00100, 0x01000380,  // RAYGUI_ICON_TARGET_MOVE_FILL
        0x01000000, 0x07c00380, 0x01000100, 0x610c2108, 0x610cfffe,
        0x01002108, 0x07c00100, 0x01000380,  // RAYGUI_ICON_CURSOR_MOVE_FILL
        0x781e0000, 0x6006700e, 0x04204812, 0x00000240, 0x02400000,
        0x48120420, 0x700e6006, 0x0000781e,  // RAYGUI_ICON_CURSOR_SCALE_FILL
        0x00000000, 0x38003c00, 0x24003000, 0x01000200, 0x00400080,
        0x000c0024, 0x003c001c, 0x00000000,  // RAYGUI_ICON_CURSOR_SCALE_RIGHT
        0x00000000, 0x001c003c, 0x0024000c, 0x00800040, 0x02000100,
        0x30002400, 0x3c003800, 0x00000000,  // RAYGUI_ICON_CURSOR_SCALE_LEFT
        0x00000000, 0x00300020, 0x10301ff8, 0x10001020, 0x10001000,
        0x10001000, 0x00001fc0, 0x00000000,  // RAYGUI_ICON_UNDO_FILL
        0x00000000, 0x0c000400, 0x0c081ff8, 0x00080408, 0x00080008,
        0x00080008, 0x000003f8, 0x00000000,  // RAYGUI_ICON_REDO_FILL
        0x00000000, 0x3ffc0000, 0x20042004, 0x20002000, 0x20402000,
        0x3ff02060, 0x00400060, 0x00000000,  // RAYGUI_ICON_REREDO_FILL
        0x00000000, 0x3ffc0000, 0x20042004, 0x27fc2004, 0x20202000,
        0x3ff82030, 0x00200030, 0x00000000,  // RAYGUI_ICON_MUTATE_FILL
        0x00000000, 0x0ff00000, 0x10081818, 0x11801008, 0x10001180,
        0x18301020, 0x00300ff8, 0x00000020,  // RAYGUI_ICON_ROTATE_FILL
        0x00000000, 0x06000200, 0x26042ffc, 0x20042204, 0x20442004,
        0x3ff42064, 0x00400060, 0x00000000,  // RAYGUI_ICON_REPEAT_FILL
        0x00000000, 0x30001000, 0x32107c0e, 0x00801120, 0x11200040,
        0x7c0e3210, 0x10003000, 0x00000000,  // RAYGUI_ICON_SHUFFLE_FILL
        0x00000000, 0x30043ffc, 0x24042804, 0x21042204, 0x20442084,
        0x20142024, 0x3ffc200c, 0x00000000,  // RAYGUI_ICON_EMPTYBOX_SMALL
        0x00000000, 0x20043ffc, 0x20042004, 0x20042004, 0x20042004,
        0x20042004, 0x3ffc2004, 0x00000000,  // RAYGUI_ICON_BOX
        0x00000000, 0x23c43ffc, 0x23c423c4, 0x200423c4, 0x20042004,
        0x20042004, 0x3ffc2004, 0x00000000,  // RAYGUI_ICON_BOX_TOP
        0x00000000, 0x3e043ffc, 0x3e043e04, 0x20043e04, 0x20042004,
        0x20042004, 0x3ffc2004, 0x00000000,  // RAYGUI_ICON_BOX_TOP_RIGHT
        0x00000000, 0x20043ffc, 0x20042004, 0x3e043e04, 0x3e043e04,
        0x20042004, 0x3ffc2004, 0x00000000,  // RAYGUI_ICON_BOX_RIGHT
        0x00000000, 0x20043ffc, 0x20042004, 0x20042004, 0x3e042004,
        0x3e043e04, 0x3ffc3e04, 0x00000000,  // RAYGUI_ICON_BOX_BOTTOM_RIGHT
        0x00000000, 0x20043ffc, 0x20042004, 0x20042004, 0x23c42004,
        0x23c423c4, 0x3ffc23c4, 0x00000000,  // RAYGUI_ICON_BOX_BOTTOM
        0x00000000, 0x20043ffc, 0x20042004, 0x20042004, 0x207c2004,
        0x207c207c, 0x3ffc207c, 0x00000000,  // RAYGUI_ICON_BOX_BOTTOM_LEFT
        0x00000000, 0x20043ffc, 0x20042004, 0x207c207c, 0x207c207c,
        0x20042004, 0x3ffc2004, 0x00000000,  // RAYGUI_ICON_BOX_LEFT
        0x00000000, 0x207c3ffc, 0x207c207c, 0x2004207c, 0x20042004,
        0x20042004, 0x3ffc2004, 0x00000000,  // RAYGUI_ICON_BOX_TOP_LEFT
        0x00000000, 0x20043ffc, 0x20042004, 0x23c423c4, 0x23c423c4,
        0x20042004, 0x3ffc2004, 0x00000000,  // RAYGUI_ICON_BOX_CIRCLE_MASK
        0x7ffe0000, 0x40024002, 0x47e24182, 0x4ff247e2, 0x47e24ff2,
        0x418247e2, 0x40024002, 0x00007ffe,  // RAYGUI_ICON_BOX_CENTER
        0x7fff0000, 0x40014001, 0x40014001, 0x49555ddd, 0x4945495d,
        0x400149c5, 0x40014001, 0x00007fff,  // RAYGUI_ICON_POT
        0x7ffe0000, 0x53327332, 0x44ce4cce, 0x41324332, 0x404e40ce,
        0x48125432, 0x4006540e, 0x00007ffe,  // RAYGUI_ICON_ALPHA_MULTIPLY
        0x7ffe0000, 0x53327332, 0x44ce4cce, 0x41324332, 0x5c4e40ce,
        0x44124432, 0x40065c0e, 0x00007ffe,  // RAYGUI_ICON_ALPHA_CLEAR
        0x7ffe0000, 0x42fe417e, 0x42fe417e, 0x42fe417e, 0x42fe417e,
        0x42fe417e, 0x42fe417e, 0x00007ffe,  // RAYGUI_ICON_DITHERING
        0x07fe0000, 0x1ffa0002, 0x7fea000a, 0x402a402a, 0x5b2a512a,
        0x5128552a, 0x40205128, 0x00007fe0,  // RAYGUI_ICON_MIPMAPS
        0x00000000, 0x1ff80000, 0x12481248, 0x12481ff8, 0x1ff81248,
        0x12481248, 0x00001ff8, 0x00000000,  // RAYGUI_ICON_BOX_GRID
        0x12480000, 0x7ffe1248, 0x12481248, 0x12487ffe, 0x7ffe1248,
        0x12481248, 0x12487ffe, 0x00001248,  // RAYGUI_ICON_GRID
        0x00000000, 0x1c380000, 0x1c3817e8, 0x08100810, 0x08100810,
        0x17e81c38, 0x00001c38, 0x00000000,  // RAYGUI_ICON_BOX_CORNERS_SMALL
        0x700e0000, 0x700e5ffa, 0x20042004, 0x20042004, 0x20042004,
        0x20042004, 0x5ffa700e, 0x0000700e,  // RAYGUI_ICON_BOX_CORNERS_BIG
        0x3f7e0000, 0x21422142, 0x21422142, 0x00003f7e, 0x21423f7e,
        0x21422142, 0x3f7e2142, 0x00000000,  // RAYGUI_ICON_FOUR_BOXES
        0x00000000, 0x3bb80000, 0x3bb83bb8, 0x3bb80000, 0x3bb83bb8,
        0x3bb80000, 0x3bb83bb8, 0x00000000,  // RAYGUI_ICON_GRID_FILL
        0x7ffe0000, 0x7ffe7ffe, 0x77fe7000, 0x77fe77fe, 0x777e7700,
        0x777e777e, 0x777e777e, 0x0000777e,  // RAYGUI_ICON_BOX_MULTISIZE
        0x781e0000, 0x40024002, 0x00004002, 0x01800000, 0x00000180,
        0x40020000, 0x40024002, 0x0000781e,  // RAYGUI_ICON_ZOOM_SMALL
        0x781e0000, 0x40024002, 0x00004002, 0x03c003c0, 0x03c003c0,
        0x40020000, 0x40024002, 0x0000781e,  // RAYGUI_ICON_ZOOM_MEDIUM
        0x781e0000, 0x40024002, 0x07e04002, 0x07e007e0, 0x07e007e0,
        0x400207e0, 0x40024002, 0x0000781e,  // RAYGUI_ICON_ZOOM_BIG
        0x781e0000, 0x5ffa4002, 0x1ff85ffa, 0x1ff81ff8, 0x1ff81ff8,
        0x5ffa1ff8, 0x40025ffa, 0x0000781e,  // RAYGUI_ICON_ZOOM_ALL
        0x00000000, 0x2004381c, 0x00002004, 0x00000000, 0x00000000,
        0x20040000, 0x381c2004, 0x00000000,  // RAYGUI_ICON_ZOOM_CENTER
        0x00000000, 0x1db80000, 0x10081008, 0x10080000, 0x00001008,
        0x10081008, 0x00001db8, 0x00000000,  // RAYGUI_ICON_BOX_DOTS_SMALL
        0x35560000, 0x00002002, 0x00002002, 0x00002002, 0x00002002,
        0x00002002, 0x35562002, 0x00000000,  // RAYGUI_ICON_BOX_DOTS_BIG
        0x7ffe0000, 0x40024002, 0x48124ff2, 0x49924812, 0x48124992,
        0x4ff24812, 0x40024002, 0x00007ffe,  // RAYGUI_ICON_BOX_CONCENTRIC
        0x00000000, 0x10841ffc, 0x10841084, 0x1ffc1084, 0x10841084,
        0x10841084, 0x00001ffc, 0x00000000,  // RAYGUI_ICON_BOX_GRID_BIG
        0x00000000, 0x00000000, 0x10000000, 0x04000800, 0x01040200,
        0x00500088, 0x00000020, 0x00000000,  // RAYGUI_ICON_OK_TICK
        0x00000000, 0x10080000, 0x04200810, 0x01800240, 0x02400180,
        0x08100420, 0x00001008, 0x00000000,  // RAYGUI_ICON_CROSS
        0x00000000, 0x02000000, 0x00800100, 0x00200040, 0x00200010,
        0x00800040, 0x02000100, 0x00000000,  // RAYGUI_ICON_ARROW_LEFT
        0x00000000, 0x00400000, 0x01000080, 0x04000200, 0x04000800,
        0x01000200, 0x00400080, 0x00000000,  // RAYGUI_ICON_ARROW_RIGHT
        0x00000000, 0x00000000, 0x00000000, 0x08081004, 0x02200410,
        0x00800140, 0x00000000, 0x00000000,  // RAYGUI_ICON_ARROW_DOWN
        0x00000000, 0x00000000, 0x01400080, 0x04100220, 0x10040808,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_ARROW_UP
        0x00000000, 0x02000000, 0x03800300, 0x03e003c0, 0x03e003f0,
        0x038003c0, 0x02000300, 0x00000000,  // RAYGUI_ICON_ARROW_LEFT_FILL
        0x00000000, 0x00400000, 0x01c000c0, 0x07c003c0, 0x07c00fc0,
        0x01c003c0, 0x004000c0, 0x00000000,  // RAYGUI_ICON_ARROW_RIGHT_FILL
        0x00000000, 0x00000000, 0x00000000, 0x0ff81ffc, 0x03e007f0,
        0x008001c0, 0x00000000, 0x00000000,  // RAYGUI_ICON_ARROW_DOWN_FILL
        0x00000000, 0x00000000, 0x01c00080, 0x07f003e0, 0x1ffc0ff8,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_ARROW_UP_FILL
        0x00000000, 0x18a008c0, 0x32881290, 0x24822686, 0x26862482,
        0x12903288, 0x08c018a0, 0x00000000,  // RAYGUI_ICON_AUDIO
        0x00000000, 0x04800780, 0x004000c0, 0x662000f0, 0x08103c30,
        0x130a0e18, 0x0000318e, 0x00000000,  // RAYGUI_ICON_FX
        0x00000000, 0x00800000, 0x08880888, 0x2aaa0a8a, 0x0a8a2aaa,
        0x08880888, 0x00000080, 0x00000000,  // RAYGUI_ICON_WAVE
        0x00000000, 0x00600000, 0x01080090, 0x02040108, 0x42044204,
        0x24022402, 0x00001800, 0x00000000,  // RAYGUI_ICON_WAVE_SINUS
        0x00000000, 0x07f80000, 0x04080408, 0x04080408, 0x04080408,
        0x7c0e0408, 0x00000000, 0x00000000,  // RAYGUI_ICON_WAVE_SQUARE
        0x00000000, 0x00000000, 0x00a00040, 0x22084110, 0x08021404,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_WAVE_TRIANGULAR
        0x00000000, 0x00000000, 0x04200000, 0x01800240, 0x02400180,
        0x00000420, 0x00000000, 0x00000000,  // RAYGUI_ICON_CROSS_SMALL
        0x00000000, 0x18380000, 0x12281428, 0x10a81128, 0x112810a8,
        0x14281228, 0x00001838, 0x00000000,  // RAYGUI_ICON_PLAYER_PREVIOUS
        0x00000000, 0x18000000, 0x11801600, 0x10181060, 0x10601018,
        0x16001180, 0x00001800, 0x00000000,  // RAYGUI_ICON_PLAYER_PLAY_BACK
        0x00000000, 0x00180000, 0x01880068, 0x18080608, 0x06081808,
        0x00680188, 0x00000018, 0x00000000,  // RAYGUI_ICON_PLAYER_PLAY
        0x00000000, 0x1e780000, 0x12481248, 0x12481248, 0x12481248,
        0x12481248, 0x00001e78, 0x00000000,  // RAYGUI_ICON_PLAYER_PAUSE
        0x00000000, 0x1ff80000, 0x10081008, 0x10081008, 0x10081008,
        0x10081008, 0x00001ff8, 0x00000000,  // RAYGUI_ICON_PLAYER_STOP
        0x00000000, 0x1c180000, 0x14481428, 0x15081488, 0x14881508,
        0x14281448, 0x00001c18, 0x00000000,  // RAYGUI_ICON_PLAYER_NEXT
        0x00000000, 0x03c00000, 0x08100420, 0x10081008, 0x10081008,
        0x04200810, 0x000003c0, 0x00000000,  // RAYGUI_ICON_PLAYER_RECORD
        0x00000000, 0x0c3007e0, 0x13c81818, 0x14281668, 0x14281428,
        0x1c381c38, 0x08102244, 0x00000000,  // RAYGUI_ICON_MAGNET
        0x07c00000, 0x08200820, 0x3ff80820, 0x23882008, 0x21082388,
        0x20082108, 0x1ff02008, 0x00000000,  // RAYGUI_ICON_LOCK_CLOSE
        0x07c00000, 0x08000800, 0x3ff80800, 0x23882008, 0x21082388,
        0x20082108, 0x1ff02008, 0x00000000,  // RAYGUI_ICON_LOCK_OPEN
        0x01c00000, 0x0c180770, 0x3086188c, 0x60832082, 0x60034781,
        0x30062002, 0x0c18180c, 0x01c00770,  // RAYGUI_ICON_CLOCK
        0x0a200000, 0x1b201b20, 0x04200e20, 0x04200420, 0x04700420,
        0x0e700e70, 0x0e700e70, 0x04200e70,  // RAYGUI_ICON_TOOLS
        0x01800000, 0x3bdc318c, 0x0ff01ff8, 0x7c3e1e78, 0x1e787c3e,
        0x1ff80ff0, 0x318c3bdc, 0x00000180,  // RAYGUI_ICON_GEAR
        0x01800000, 0x3ffc318c, 0x1c381ff8, 0x781e1818, 0x1818781e,
        0x1ff81c38, 0x318c3ffc, 0x00000180,  // RAYGUI_ICON_GEAR_BIG
        0x00000000, 0x08080ff8, 0x08081ffc, 0x0aa80aa8, 0x0aa80aa8,
        0x0aa80aa8, 0x08080aa8, 0x00000ff8,  // RAYGUI_ICON_BIN
        0x00000000, 0x00000000, 0x20043ffc, 0x08043f84, 0x04040f84,
        0x04040784, 0x000007fc, 0x00000000,  // RAYGUI_ICON_HAND_POINTER
        0x00000000, 0x24400400, 0x00001480, 0x6efe0e00, 0x00000e00,
        0x24401480, 0x00000400, 0x00000000,  // RAYGUI_ICON_LASER
        0x00000000, 0x03c00000, 0x08300460, 0x11181118, 0x11181118,
        0x04600830, 0x000003c0, 0x00000000,  // RAYGUI_ICON_COIN
        0x00000000, 0x10880080, 0x06c00810, 0x366c07e0, 0x07e00240,
        0x00001768, 0x04200240, 0x00000000,  // RAYGUI_ICON_EXPLOSION
        0x00000000, 0x3d280000, 0x2528252c, 0x3d282528, 0x05280528,
        0x05e80528, 0x00000000, 0x00000000,  // RAYGUI_ICON_1UP
        0x01800000, 0x03c003c0, 0x018003c0, 0x0ff007e0, 0x0bd00bd0,
        0x0a500bd0, 0x02400240, 0x02400240,  // RAYGUI_ICON_PLAYER
        0x01800000, 0x03c003c0, 0x118013c0, 0x03c81ff8, 0x07c003c8,
        0x04400440, 0x0c080478, 0x00000000,  // RAYGUI_ICON_PLAYER_JUMP
        0x3ff80000, 0x30183ff8, 0x30183018, 0x3ff83ff8, 0x03000300,
        0x03c003c0, 0x03e00300, 0x000003e0,  // RAYGUI_ICON_KEY
        0x3ff80000, 0x3ff83ff8, 0x33983ff8, 0x3ff83398, 0x3ff83ff8,
        0x00000540, 0x0fe00aa0, 0x00000fe0,  // RAYGUI_ICON_DEMON
        0x00000000, 0x0ff00000, 0x20041008, 0x25442004, 0x10082004,
        0x06000bf0, 0x00000300, 0x00000000,  // RAYGUI_ICON_TEXT_POPUP
        0x00000000, 0x11440000, 0x07f00be8, 0x1c1c0e38, 0x1c1c0c18,
        0x07f00e38, 0x11440be8, 0x00000000,  // RAYGUI_ICON_GEAR_EX
        0x00000000, 0x20080000, 0x0c601010, 0x07c00fe0, 0x07c007c0,
        0x0c600fe0, 0x20081010, 0x00000000,  // RAYGUI_ICON_CRACK
        0x00000000, 0x20080000, 0x0c601010, 0x04400fe0, 0x04405554,
        0x0c600fe0, 0x20081010, 0x00000000,  // RAYGUI_ICON_CRACK_POINTS
        0x00000000, 0x00800080, 0x01c001c0, 0x1ffc3ffe, 0x03e007f0,
        0x07f003e0, 0x0c180770, 0x00000808,  // RAYGUI_ICON_STAR
        0x0ff00000, 0x08180810, 0x08100818, 0x0a100810, 0x08180810,
        0x08100818, 0x08100810, 0x00001ff8,  // RAYGUI_ICON_DOOR
        0x0ff00000, 0x08100810, 0x08100810, 0x10100010, 0x4f902010,
        0x10102010, 0x08100010, 0x00000ff0,  // RAYGUI_ICON_EXIT
        0x00040000, 0x001f000e, 0x0ef40004, 0x12f41284, 0x0ef41214,
        0x10040004, 0x7ffc3004, 0x10003000,  // RAYGUI_ICON_MODE_2D
        0x78040000, 0x501f600e, 0x0ef44004, 0x12f41284, 0x0ef41284,
        0x10140004, 0x7ffc300c, 0x10003000,  // RAYGUI_ICON_MODE_3D
        0x7fe00000, 0x50286030, 0x47fe4804, 0x44224402, 0x44224422,
        0x241275e2, 0x0c06140a, 0x000007fe,  // RAYGUI_ICON_CUBE
        0x7fe00000, 0x5ff87ff0, 0x47fe4ffc, 0x44224402, 0x44224422,
        0x241275e2, 0x0c06140a, 0x000007fe,  // RAYGUI_ICON_CUBE_FACE_TOP
        0x7fe00000, 0x50386030, 0x47fe483c, 0x443e443e, 0x443e443e,
        0x241e75fe, 0x0c06140e, 0x000007fe,  // RAYGUI_ICON_CUBE_FACE_LEFT
        0x7fe00000, 0x50286030, 0x47fe4804, 0x47fe47fe, 0x47fe47fe,
        0x27fe77fe, 0x0ffe17fe, 0x000007fe,  // RAYGUI_ICON_CUBE_FACE_FRONT
        0x7fe00000, 0x50286030, 0x47fe4804, 0x44224402, 0x44224422,
        0x3ff27fe2, 0x0ffe1ffa, 0x000007fe,  // RAYGUI_ICON_CUBE_FACE_BOTTOM
        0x7fe00000, 0x70286030, 0x7ffe7804, 0x7c227c02, 0x7c227c22,
        0x3c127de2, 0x0c061c0a, 0x000007fe,  // RAYGUI_ICON_CUBE_FACE_RIGHT
        0x7fe00000, 0x7fe87ff0, 0x7ffe7fe4, 0x7fe27fe2, 0x7fe27fe2,
        0x24127fe2, 0x0c06140a, 0x000007fe,  // RAYGUI_ICON_CUBE_FACE_BACK
        0x00000000, 0x2a0233fe, 0x22022602, 0x22022202, 0x2a022602,
        0x00a033fe, 0x02080110, 0x00000000,  // RAYGUI_ICON_CAMERA
        0x00000000, 0x200c3ffc, 0x000c000c, 0x3ffc000c, 0x30003000,
        0x30003000, 0x3ffc3004, 0x00000000,  // RAYGUI_ICON_SPECIAL
        0x00000000, 0x0022003e, 0x012201e2, 0x0100013e, 0x01000100,
        0x79000100, 0x4f004900, 0x00007800,  // RAYGUI_ICON_LINK_NET
        0x00000000, 0x44007c00, 0x45004600, 0x00627cbe, 0x00620022,
        0x45007cbe, 0x44004600, 0x00007c00,  // RAYGUI_ICON_LINK_BOXES
        0x00000000, 0x0044007c, 0x0010007c, 0x3f100010, 0x3f1021f0,
        0x3f100010, 0x3f0021f0, 0x00000000,  // RAYGUI_ICON_LINK_MULTI
        0x00000000, 0x0044007c, 0x00440044, 0x0010007c, 0x00100010,
        0x44107c10, 0x440047f0, 0x00007c00,  // RAYGUI_ICON_LINK
        0x00000000, 0x0044007c, 0x00440044, 0x0000007c, 0x00000010,
        0x44007c10, 0x44004550, 0x00007c00,  // RAYGUI_ICON_LINK_BROKE
        0x02a00000, 0x22a43ffc, 0x20042004, 0x20042ff4, 0x20042ff4,
        0x20042ff4, 0x20042004, 0x00003ffc,  // RAYGUI_ICON_TEXT_NOTES
        0x3ffc0000, 0x20042004, 0x245e27c4, 0x27c42444, 0x2004201e,
        0x201e2004, 0x20042004, 0x00003ffc,  // RAYGUI_ICON_NOTEBOOK
        0x00000000, 0x07e00000, 0x04200420, 0x24243ffc, 0x24242424,
        0x24242424, 0x3ffc2424, 0x00000000,  // RAYGUI_ICON_SUITCASE
        0x00000000, 0x0fe00000, 0x08200820, 0x40047ffc, 0x7ffc5554,
        0x40045554, 0x7ffc4004, 0x00000000,  // RAYGUI_ICON_SUITCASE_ZIP
        0x00000000, 0x20043ffc, 0x3ffc2004, 0x13c81008, 0x100813c8,
        0x10081008, 0x1ff81008, 0x00000000,  // RAYGUI_ICON_MAILBOX
        0x00000000, 0x40027ffe, 0x5ffa5ffa, 0x5ffa5ffa, 0x40025ffa,
        0x03c07ffe, 0x1ff81ff8, 0x00000000,  // RAYGUI_ICON_MONITOR
        0x0ff00000, 0x6bfe7ffe, 0x7ffe7ffe, 0x68167ffe, 0x08106816,
        0x08100810, 0x0ff00810, 0x00000000,  // RAYGUI_ICON_PRINTER
        0x3ff80000, 0xfffe2008, 0x870a8002, 0x904a888a, 0x904a904a,
        0x870a888a, 0xfffe8002, 0x00000000,  // RAYGUI_ICON_PHOTO_CAMERA
        0x0fc00000, 0xfcfe0cd8, 0x8002fffe, 0x84428382, 0x84428442,
        0x80028382, 0xfffe8002, 0x00000000,  // RAYGUI_ICON_PHOTO_CAMERA_FLASH
        0x00000000, 0x02400180, 0x08100420, 0x20041008, 0x23c42004,
        0x22442244, 0x3ffc2244, 0x00000000,  // RAYGUI_ICON_HOUSE
        0x00000000, 0x1c700000, 0x3ff83ef8, 0x3ff83ff8, 0x0fe01ff0,
        0x038007c0, 0x00000100, 0x00000000,  // RAYGUI_ICON_HEART
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x80000000, 0xe000c000,  // RAYGUI_ICON_CORNER
        0x00000000, 0x14001c00, 0x15c01400, 0x15401540, 0x155c1540,
        0x15541554, 0x1ddc1554, 0x00000000,  // RAYGUI_ICON_VERTICAL_BARS
        0x00000000, 0x03000300, 0x1b001b00, 0x1b601b60, 0x1b6c1b60,
        0x1b6c1b6c, 0x1b6c1b6c, 0x00000000,  // RAYGUI_ICON_VERTICAL_BARS_FILL
        0x00000000, 0x00000000, 0x403e7ffe, 0x7ffe403e, 0x7ffe0000,
        0x43fe43fe, 0x00007ffe, 0x00000000,  // RAYGUI_ICON_LIFE_BARS
        0x7ffc0000, 0x43844004, 0x43844284, 0x43844004, 0x42844284,
        0x42844284, 0x40044384, 0x00007ffc,  // RAYGUI_ICON_INFO
        0x40008000, 0x10002000, 0x04000800, 0x01000200, 0x00400080,
        0x00100020, 0x00040008, 0x00010002,  // RAYGUI_ICON_CROSSLINE
        0x00000000, 0x1ff01ff0, 0x18301830, 0x1f001830, 0x03001f00,
        0x00000300, 0x03000300, 0x00000000,  // RAYGUI_ICON_HELP
        0x3ff00000, 0x2abc3550, 0x2aac3554, 0x2aac3554, 0x2aac3554,
        0x2aac3554, 0x2aac3554, 0x00003ffc,  // RAYGUI_ICON_FILETYPE_ALPHA
        0x3ff00000, 0x201c2010, 0x22442184, 0x28142424, 0x29942814,
        0x2ff42994, 0x20042004, 0x00003ffc,  // RAYGUI_ICON_FILETYPE_HOME
        0x07fe0000, 0x04020402, 0x7fe20402, 0x44224422, 0x44224422,
        0x402047fe, 0x40204020, 0x00007fe0,  // RAYGUI_ICON_LAYERS_VISIBLE
        0x07fe0000, 0x04020402, 0x7c020402, 0x44024402, 0x44024402,
        0x402047fe, 0x40204020, 0x00007fe0,  // RAYGUI_ICON_LAYERS
        0x00000000, 0x40027ffe, 0x7ffe4002, 0x40024002, 0x40024002,
        0x40024002, 0x7ffe4002, 0x00000000,  // RAYGUI_ICON_WINDOW
        0x09100000, 0x09f00910, 0x09100910, 0x00000910, 0x24a2779e,
        0x27a224a2, 0x709e20a2, 0x00000000,  // RAYGUI_ICON_HIDPI
        0x00000000, 0x01800180, 0x01800180, 0x3ffc0180, 0x01803ffc,
        0x01800180, 0x01800180, 0x00000000,  // RAYGUI_ICON_PLUS
        0x00000000, 0x00000000, 0x00000000, 0x3ffc0000, 0x00003ffc,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_MINUS
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_202
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_203
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_204
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_205
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_206
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_207
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_208
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_209
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_210
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_211
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_212
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_213
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_214
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_215
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_216
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_217
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_218
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_219
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_220
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_221
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_222
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_223
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_224
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_225
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_226
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_227
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_228
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_229
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_230
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_231
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_232
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_233
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_234
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_235
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_236
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_237
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_238
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_239
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_240
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_241
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_242
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_243
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_244
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_245
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_246
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_247
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_248
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_249
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_250
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_251
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_252
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_253
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_254
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,  // RAYGUI_ICON_255
};

// Global gui state control functions
RAYGUIAPI void GuiEnable(void);       // Enable gui controls (global state)
RAYGUIAPI void GuiDisable(void);      // Disable gui controls (global state)
RAYGUIAPI void GuiLock(void);         // Lock gui controls (global state)
RAYGUIAPI void GuiUnlock(void);       // Unlock gui controls (global state)
RAYGUIAPI bool GuiIsLocked(void);     // Check if gui is locked (global state)
RAYGUIAPI void GuiFade(float alpha);  // Set gui controls alpha (global state),
                                      // alpha goes from 0.0f to 1.0f
RAYGUIAPI void GuiSetState(int state);  // Set gui state (global state)
RAYGUIAPI int GuiGetState(void);        // Get gui state (global state)

// Font set/get functions
RAYGUIAPI void GuiSetFont(Font font);  // Set gui custom font (global state)
RAYGUIAPI Font GuiGetFont(void);       // Get gui custom font (global state)

// Style set/get functions
RAYGUIAPI void GuiSetStyle(int control, int property,
                           int value);                 // Set one style property
RAYGUIAPI int GuiGetStyle(int control, int property);  // Get one style property

// Container/separator controls, useful for controls organization
RAYGUIAPI bool GuiWindowBox(Rectangle bounds,
                            const char *title);  // Window Box control, shows a
                                                 // window that can be closed
RAYGUIAPI void GuiGroupBox(
    Rectangle bounds, const char *text);  // Group Box control with text name
RAYGUIAPI void GuiLine(
    Rectangle bounds,
    const char *text);  // Line separator control, could contain text
RAYGUIAPI void GuiPanel(
    Rectangle bounds);  // Panel control, useful to group controls
RAYGUIAPI Rectangle GuiScrollPanel(Rectangle bounds, Rectangle content,
                                   Vector2 *scroll);  // Scroll Panel control

// Basic controls set
RAYGUIAPI void GuiLabel(Rectangle bounds,
                        const char *text);  // Label control, shows text
RAYGUIAPI bool GuiButton(
    Rectangle bounds,
    const char *text);  // Button control, returns true when clicked
RAYGUIAPI bool GuiButtonWithColor(
    Rectangle bounds, const char *text,
    const Color color);  // Button control with color, returns true when clicked
RAYGUIAPI bool GuiLabelButton(
    Rectangle bounds,
    const char *text);  // Label button control, show true when clicked
RAYGUIAPI bool GuiToggle(
    Rectangle bounds, const char *text,
    bool active);  // Toggle Button control, returns true when active
RAYGUIAPI int GuiToggleGroup(
    Rectangle bounds, const char *text,
    int active);  // Toggle Group control, returns active toggle index
RAYGUIAPI bool GuiCheckBox(
    Rectangle bounds, const char *text,
    bool checked);  // Check Box control, returns true when active
RAYGUIAPI int GuiComboBox(
    Rectangle bounds, const char *text,
    int active);  // Combo Box control, returns selected item index
RAYGUIAPI bool GuiDropdownBox(
    Rectangle bounds, const char *text, int *active,
    bool editMode);  // Dropdown Box control, returns selected item
RAYGUIAPI bool GuiSpinner(
    Rectangle bounds, const char *text, int *value, int minValue, int maxValue,
    bool editMode);  // Spinner control, returns selected value
RAYGUIAPI bool GuiValueBox(
    Rectangle bounds, const char *text, int *value, int minValue, int maxValue,
    bool editMode);  // Value Box control, updates input text with numbers
RAYGUIAPI bool GuiTextBox(
    Rectangle bounds, char *text, int textSize,
    bool editMode);  // Text Box control, updates input text
RAYGUIAPI bool GuiTextBoxMulti(
    Rectangle bounds, char *text, int textSize,
    bool editMode);  // Text Box control with multiple lines
RAYGUIAPI float GuiSlider(
    Rectangle bounds, const char *textLeft, const char *textRight, float value,
    float minValue, float maxValue);  // Slider control, returns selected value
RAYGUIAPI float GuiSliderBar(
    Rectangle bounds, const char *textLeft, const char *textRight, float value,
    float minValue,
    float maxValue);  // Slider Bar control, returns selected value
RAYGUIAPI float GuiProgressBar(
    Rectangle bounds, const char *textLeft, const char *textRight, float value,
    float minValue,
    float maxValue);  // Progress Bar control, shows current progress value
RAYGUIAPI void GuiStatusBar(
    Rectangle bounds, const char *text);  // Status Bar control, shows info text
RAYGUIAPI void GuiDummyRec(Rectangle bounds,
                           const char *text);  // Dummy control for placeholders
RAYGUIAPI int GuiScrollBar(Rectangle bounds, int value, int minValue,
                           int maxValue);  // Scroll Bar control
RAYGUIAPI Vector2 GuiGrid(Rectangle bounds, float spacing,
                          int subdivs);  // Grid control

// Advance controls set
RAYGUIAPI int GuiListView(
    Rectangle bounds, const char *text, int *scrollIndex,
    int active);  // List View control, returns selected list item index
RAYGUIAPI int GuiListViewEx(Rectangle bounds, const char **text, int count,
                            int *focus, int *scrollIndex,
                            int active);  // List View with extended parameters
RAYGUIAPI int GuiMessageBox(
    Rectangle bounds, const char *title, const char *message,
    const char *buttons);  // Message Box control, displays a message
RAYGUIAPI int GuiTextInputBox(
    Rectangle bounds, const char *title, const char *message,
    const char *buttons, char *text);  // Text Input Box control, ask for text
RAYGUIAPI Color
GuiColorPicker(Rectangle bounds,
               Color color);  // Color Picker control (multiple color controls)
RAYGUIAPI Color GuiColorPanel(Rectangle bounds,
                              Color color);  // Color Panel control
RAYGUIAPI float GuiColorBarAlpha(Rectangle bounds,
                                 float alpha);  // Color Bar Alpha control
RAYGUIAPI float GuiColorBarHue(Rectangle bounds,
                               float value);  // Color Bar Hue control

// Styles loading functions
RAYGUIAPI void GuiLoadStyle(
    const char *fileName);  // Load style file over global style variable (.rgs)
RAYGUIAPI void GuiLoadStyleDefault(
    void);  // Load style default over global style

// Icons functionality
RAYGUIAPI const char *GuiIconText(
    int iconId,
    const char *text);  // Get text with icon id prepended (if supported)
#if !defined(RAYGUI_NO_ICONS)
RAYGUIAPI void GuiDrawIcon(int iconId, int posX, int posY, int pixelSize,
                           Color color);

RAYGUIAPI unsigned int *GuiGetIcons(void);  // Get full icons data pointer
RAYGUIAPI unsigned int *GuiGetIconData(int iconId);  // Get icon bit data
RAYGUIAPI void GuiSetIconData(int iconId,
                              unsigned int *data);  // Set icon bit data

RAYGUIAPI void GuiSetIconPixel(int iconId, int x,
                               int y);  // Set icon pixel value
RAYGUIAPI void GuiClearIconPixel(int iconId, int x,
                                 int y);  // Clear icon pixel value
RAYGUIAPI bool GuiCheckIconPixel(int iconId, int x,
                                 int y);  // Check icon pixel value
#endif

#if defined(__cplusplus)
}  // Prevents name mangling of functions
#endif

#endif  // RAYGUI_H
