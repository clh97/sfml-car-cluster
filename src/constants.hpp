#define CAR_CLUSTER_VERSION_MAJOR @CAR_CLUSTER_VERSION_MAJOR @
#define CAR_CLUSTER_VERSION_MINOR @CAR_CLUSTER_VERSION_MINOR @

/* COLORS*/
#define THEME_COLOR_WHITE ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
#define THEME_COLOR_BLACK ImVec4(0.0f, 0.0f, 0.0f, 1.0f)
#define THEME_COLOR_RED ImVec4(1.0f, 0.0f, 0.0f, 1.0f)
#define THEME_COLOR_GREEN ImVec4(0.0f, 1.0f, 0.0f, 1.0f)
#define THEME_COLOR_BLUE ImVec4(0.0f, 0.0f, 1.0f, 1.0f)
#define THEME_COLOR_YELLOW ImVec4(1.0f, 1.0f, 0.0f, 1.0f)
#define THEME_COLOR_PURPLE ImVec4(1.0f, 0.0f, 1.0f, 1.0f)
#define THEME_COLOR_CYAN ImVec4(0.0f, 1.0f, 1.0f, 1.0f)
#define THEME_COLOR_ORANGE ImVec4(1.0f, 0.5f, 0.0f, 1.0f)
#define THEME_COLOR_GRAY ImVec4(0.5f, 0.5f, 0.5f, 1.0f)
#define THEME_COLOR_DARK_GRAY ImVec4(0.25f, 0.25f, 0.25f, 1.0f)
#define THEME_COLOR_LIGHT_GRAY ImVec4(0.75f, 0.75f, 0.75f, 1.0f)
#define THEME_COLOR_TRANSPARENT ImVec4(0.0f, 0.0f, 0.0f, 0.0f)

/* THEME COLORS */
#define THEME_COLOR_BLUE_1 ImVec4(0.22f, 0.26f, 0.73f, 1.0f)


#define SKIP_SPLASH true
#define SPLASH_FADEIN_TIME 2.0f
#define SPLASH_FADEOUT_TIME 1.15f

#define WINDOW_RESOLUTION_FACTOR 2.0f
#define WINDOW_TITLE "Car Cluster"
#define WINDOW_WIDTH 1920 * WINDOW_RESOLUTION_FACTOR
#define WINDOW_HEIGHT 550 * WINDOW_RESOLUTION_FACTOR
#define WINDOW_STYLE sf::Style::Default

#define MAX_FPS 144

#define FORD_LOGO_PATH "assets/ford.png"
#define FONT_PATH "assets/OpenSans-Light.ttf"

#define SPEEDOMETER_RADIUS 225 * WINDOW_RESOLUTION_FACTOR
#define SPEEDOMETER_X WINDOW_WIDTH / 1.5 - SPEEDOMETER_RADIUS / 2
#define SPEEDOMETER_Y WINDOW_HEIGHT / 2 - SPEEDOMETER_RADIUS / 2

#define TACHOMETER_RADIUS 225 * WINDOW_RESOLUTION_FACTOR
#define TACHOMETER_X WINDOW_WIDTH / 4 - TACHOMETER_RADIUS / 2
#define TACHOMETER_Y WINDOW_HEIGHT / 2 - TACHOMETER_RADIUS / 2

#define FUEL_WIDTH 100 * WINDOW_RESOLUTION_FACTOR
#define FUEL_HEIGHT 100 * WINDOW_RESOLUTION_FACTOR
#define FUEL_X WINDOW_WIDTH / 1.25f - FUEL_WIDTH / 2
#define FUEL_Y WINDOW_HEIGHT * 0.5f - FUEL_HEIGHT / 2

/* Value limits */
#define SPEEDOMETER_MIN_VALUE 0.0f
#define SPEEDOMETER_MAX_VALUE 200.0f

#define TACHOMETER_MIN_VALUE 0.0f
#define TACHOMETER_MAX_VALUE 8000.0f

#define FUEL_MIN_VALUE 0.0f
#define FUEL_MAX_VALUE 100.0f

#define OIL_MIN_VALUE 0.0f
#define OIL_MAX_VALUE 100.0f

#define TEMPERATURE_MIN_VALUE 0.0f
#define TEMPERATURE_MAX_VALUE 100.0f

// macro for getting the multiplication factor for two value limits (used on config ui to get the multiplication factor for automatic values setting)
#define VALUE_LIMIT_MULTIPLICATION_FACTOR(min_value, max_value) max_value / (pow(1.33f, log10(max_value)))
