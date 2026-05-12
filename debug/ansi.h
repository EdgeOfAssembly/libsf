ifndef COLORS_H
#define COLORS_H

// Color codes
#define COLOR_BLACK   "\x1b[30m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_WHITE   "\x1b[37m"
#define COLOR_RESET   "\x1b[0m"

// Bright colors
#define COLOR_BRIGHT_BLACK   "\x1b[90m"
#define COLOR_BRIGHT_RED     "\x1b[91m"
#define COLOR_BRIGHT_GREEN   "\x1b[92m"
#define COLOR_BRIGHT_YELLOW  "\x1b[93m"
#define COLOR_BRIGHT_BLUE    "\x1b[94m"
#define COLOR_BRIGHT_MAGENTA "\x1b[95m"
#define COLOR_BRIGHT_CYAN    "\x1b[96m"
#define COLOR_BRIGHT_WHITE   "\x1b[97m"

// Background colors
#define COLOR_BG_BLACK   "\x1b[40m"
#define COLOR_BG_RED     "\x1b[41m"
#define COLOR_BG_GREEN   "\x1b[42m"
#define COLOR_BG_YELLOW  "\x1b[43m"
#define COLOR_BG_BLUE    "\x1b[44m"
#define COLOR_BG_MAGENTA "\x1b[45m"
#define COLOR_BG_CYAN    "\x1b[46m"
#define COLOR_BG_WHITE   "\x1b[47m"

// Bright background colors
#define COLOR_BG_BRIGHT_BLACK   "\x1b[100m"
#define COLOR_BG_BRIGHT_RED     "\x1b[101m"
#define COLOR_BG_BRIGHT_GREEN   "\x1b[102m"
#define COLOR_BG_BRIGHT_YELLOW  "\x1b[103m"
#define COLOR_BG_BRIGHT_BLUE    "\x1b[104m"
#define COLOR_BG_BRIGHT_MAGENTA "\x1b[105m"
#define COLOR_BG_BRIGHT_CYAN    "\x1b[106m"
#define COLOR_BG_BRIGHT_WHITE   "\x1b[107m"

// Erase codes
#define ERASE_TO_END         "\x1b[0J"
#define ERASE_FROM_BEGIN     "\x1b[1J"
#define ERASE_SCREEN         "\x1b[2J"
#define ERASE_SAVED_LINES    "\x1b[3J"
#define ERASE_LINE           "\x1b[0K"
#define ERASE_LINE_TO_END    "\x1b[0K"
#define ERASE_LINE_FROM_BEGIN "\x1b[1K"
#define ERASE_LINE_FULL      "\x1b[2K"

// Cursor movement
#define CURSOR_HOME          "\x1b[H"
#define CURSOR_MOVE(x,y)     "\x1b[" #y ";" #x "H"
#define CURSOR_MOVE_FORMAT(x,y) "\x1b[" #y ";" #x "f"
#define CURSOR_UP(n)         "\x1b[" #n "A"
#define CURSOR_DOWN(n)       "\x1b[" #n "B"
#define CURSOR_RIGHT(n)      "\x1b[" #n "C"
#define CURSOR_LEFT(n)       "\x1b[" #n "D"
#define CURSOR_NEXT_LINE(n)  "\x1b[" #n "E"
#define CURSOR_PREV_LINE(n)  "\x1b[" #n "F"
#define CURSOR_COLUMN(n)     "\x1b[" #n "G"
#define CURSOR_REQUEST_POS   "\x1b[6n"
#define CURSOR_UP_ONE        "\x1b M"
#define CURSOR_SAVE_DEC      "\x1b7"
#define CURSOR_RESTORE_DEC   "\x1b8"
#define CURSOR_SAVE_SCO      "\x1bs"
#define CURSOR_RESTORE_SCO   "\x1bu"

// Mode settings
#define MODE_HIDE_CURSOR     "\x1b[?25l"
#define MODE_SHOW_CURSOR     "\x1b[?25h"
#define MODE_RESET           "\x1b[!p"
#define MODE_SET_LINE_WRAP   "\x1b[?7h"
#define MODE_RESET_LINE_WRAP "\x1b[?7l"
#define MODE_ENABLE_KEYPAD   "\x1b[?1h"
#define MODE_DISABLE_KEYPAD  "\x1b[?1l"
#define MODE_ENABLE_MOUSE    "\x1b[?1000h"
#define MODE_DISABLE_MOUSE   "\x1b[?1000l"
#define MODE_ENABLE_FOCUS    "\x1b[?1004h"
#define MODE_DISABLE_FOCUS   "\x1b[?1004l"

// Screen Modes
#define MODE_ALTERNATE_SCREEN   "\x1b[?1049h"
#define MODE_NORMAL_SCREEN      "\x1b[?1049l"

// Screen width or type change
#define MODE_40X25_MONO         "\x1b[=0h"
#define MODE_40X25_COLOR        "\x1b[=1h"
#define MODE_80X25_MONO         "\x1b[=2h"
#define MODE_80X25_COLOR        "\x1b[=3h"
#define MODE_320X200_4COLOR     "\x1b[=4h"
#define MODE_320X200_MONO       "\x1b[=5h"
#define MODE_640X200_MONO       "\x1b[=6h"
#define MODE_LINE_WRAP          "\x1b[=7h"
#define MODE_320X200_COLOR      "\x1b[=13h"
#define MODE_640X200_16COLOR    "\x1b[=14h"
#define MODE_640X350_MONO       "\x1b[=15h"
#define MODE_640X350_16COLOR    "\x1b[=16h"
#define MODE_640X480_MONO       "\x1b[=17h"
#define MODE_640X480_16COLOR    "\x1b[=18h"
#define MODE_320X200_256COLOR   "\x1b[=19h"

// Colors / Graphics Mode
#define MODE_GRAPHICS_RESET     "\x1b[0m"
#define MODE_BOLD               "\x1b[1m"
#define MODE_BOLD_RESET         "\x1b[22m"
#define MODE_FAINT              "\x1b[2m"
#define MODE_FAINT_RESET        "\x1b[22m"
#define MODE_ITALIC             "\x1b[3m"
#define MODE_ITALIC_RESET       "\x1b[23m"
#define MODE_UNDERLINE          "\x1b[4m"
#define MODE_UNDERLINE_RESET    "\x1b[24m"
#define MODE_BLINK              "\x1b[5m"
#define MODE_BLINK_RESET        "\x1b[25m"
#define MODE_REVERSE            "\x1b[7m"
#define MODE_REVERSE_RESET      "\x1b[27m"
#define MODE_CONCEAL            "\x1b[8m"
#define MODE_CONCEAL_RESET      "\x1b[28m"
#define MODE_STRIKETHROUGH      "\x1b[9m"
#define MODE_STRIKETHROUGH_RESET "\x1b[29m"

#endif // COLORS_H

