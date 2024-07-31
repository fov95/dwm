/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 4;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const int swallowfloating         = 0;   /* 1 means swallow floating windows by default */
static int nomodbuttons                  = 1;   /* allow client mouse button bindings that have no modifier */
static const unsigned int gappih         = 20;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 20;  /* vert inner gap between windows */
static const unsigned int gappoh         = 20;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 20;  /* vert outer gap between windows and screen edge */
static const int smartgaps_fact          = 1;   /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_TOP_LEFT_SQUARE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_TOP_LEFT_SQUARE;
static int fakefsindicatortype           = INDICATOR_PLUS;
static int floatfakefsindicatortype      = INDICATOR_PLUS_AND_LARGER_SQUARE;
static const char *fonts[]               = { "monospace:size=10" };
static const char dmenufont[]            = "monospace:size=10";

static char c000000[]                    = "#000000"; // placeholder value

static char normfgcolor[]                = "#bbbbbb";
static char normbgcolor[]                = "#222222";
static char normbordercolor[]            = "#444444";
static char normfloatcolor[]             = "#db8fd9";

static char selfgcolor[]                 = "#eeeeee";
static char selbgcolor[]                 = "#005577";
static char selbordercolor[]             = "#005577";
static char selfloatcolor[]              = "#005577";

static char titlenormfgcolor[]           = "#bbbbbb";
static char titlenormbgcolor[]           = "#222222";
static char titlenormbordercolor[]       = "#444444";
static char titlenormfloatcolor[]        = "#db8fd9";

static char titleselfgcolor[]            = "#eeeeee";
static char titleselbgcolor[]            = "#005577";
static char titleselbordercolor[]        = "#005577";
static char titleselfloatcolor[]         = "#005577";

static char tagsnormfgcolor[]            = "#bbbbbb";
static char tagsnormbgcolor[]            = "#222222";
static char tagsnormbordercolor[]        = "#444444";
static char tagsnormfloatcolor[]         = "#db8fd9";

static char tagsselfgcolor[]             = "#eeeeee";
static char tagsselbgcolor[]             = "#005577";
static char tagsselbordercolor[]         = "#005577";
static char tagsselfloatcolor[]          = "#005577";

static char hidnormfgcolor[]             = "#005577";
static char hidselfgcolor[]              = "#227799";
static char hidnormbgcolor[]             = "#222222";
static char hidselbgcolor[]              = "#222222";

static char urgfgcolor[]                 = "#bbbbbb";
static char urgbgcolor[]                 = "#222222";
static char urgbordercolor[]             = "#ff0000";
static char urgfloatcolor[]              = "#db8fd9";



static char *colors[][ColCount] = {
	/*                       fg                bg                border                float */
	[SchemeNorm]         = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
	[SchemeSel]          = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
	[SchemeTitleNorm]    = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
	[SchemeTitleSel]     = { titleselfgcolor,  titleselbgcolor,  titleselbordercolor,  titleselfloatcolor },
	[SchemeTagsNorm]     = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
	[SchemeTagsSel]      = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
	[SchemeHidNorm]      = { hidnormfgcolor,   hidnormbgcolor,   c000000,              c000000 },
	[SchemeHidSel]       = { hidselfgcolor,    hidselbgcolor,    c000000,              c000000 },
	[SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
};


static const char *const autostart[] = {
	"run_once", NULL,
	"set_theme", NULL,
	NULL /* terminate */
};


/* Tags
 * In a traditional dwm the number of tags in use can be changed simply by changing the number
 * of strings in the tags array. This build does things a bit different which has some added
 * benefits. If you need to change the number of tags here then change the NUMTAGS macro in dwm.c.
 *
 * Examples:
 *
 *  1) static char *tagicons[][NUMTAGS*2] = {
 *         [DEFAULT_TAGS] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I" },
 *     }
 *
 *  2) static char *tagicons[][1] = {
 *         [DEFAULT_TAGS] = { "•" },
 *     }
 *
 * The first example would result in the tags on the first monitor to be 1 through 9, while the
 * tags for the second monitor would be named A through I. A third monitor would start again at
 * 1 through 9 while the tags on a fourth monitor would also be named A through I. Note the tags
 * count of NUMTAGS*2 in the array initialiser which defines how many tag text / icon exists in
 * the array. This can be changed to *3 to add separate icons for a third monitor.
 *
 * For the second example each tag would be represented as a bullet point. Both cases work the
 * same from a technical standpoint - the icon index is derived from the tag index and the monitor
 * index. If the icon index is is greater than the number of tag icons then it will wrap around
 * until it an icon matches. Similarly if there are two tag icons then it would alternate between
 * them. This works seamlessly with alternative tags and alttagsdecoration patches.
 */
static char *tagicons[][NUMTAGS] = {
	[DEFAULT_TAGS]        = { "", "", "", "", "" },
	/* [DEFAULT_TAGS]        = { " 1 ", "2 ", "3 ", "4 ", "5 " }, */
	[ALTERNATIVE_TAGS]    = { "A", "B", "C", "D", "E", "F" },
	[ALT_TAGS_DECORATION] = { "<1>", "<2>", "<3>", "<4>", "<5>" },
};


/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */
static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     *	WM_WINDOW_ROLE(STRING) = role
     *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
     */
    RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
    RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
    RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
    RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
    RULE(.class = "firefoxone", .tags = 1 << 0)
    RULE(.class = "Tor Browser", .tags = 1 << 0, .isfloating = 1, .iscentered = 1)
    RULE(.class = "firefoxtwo", .tags = 1 << 1)
    RULE(.class = "FreeTube", .tags = 1 << 1)
    RULE(.class = "Chromium", .tags = 1 << 2)
    RULE(.class = "thunderbird", .tags = 1 << 3)
    RULE(.class = "Steam", .tags = 1 << 4)
    RULE(.class = "steam", .tags = 1 << 4)
    RULE(.instance = "steam", .tags = 1 << 4)
    RULE(.instance = "steamwebhelper", .tags = 1 << 4)
    RULE(.title = "Steam", .tags = 1 << 4)
    RULE(.title = "Special Offers", .tags = 1 << 4)
    RULE(.title = "Extract", .isfloating = 1)
    RULE(.title = "steam", .tags = 1 << 4)
    RULE(.title = "Steam - News", .tags = 1 << 4, .isfloating = 1, .iscentered = 1)
    RULE(.title = "Image Popout", .tags = 1 << 4, .isfloating = 1, .iscentered = 1)
    RULE(.class = "KeePassXC", .isfloating = 1)
    RULE(.class = "eww-bar", .isfloating = 1)
    RULE(.class = "Dmenu", .isfloating = 1)
    RULE(.class = "Dunst", .isfloating = 1)
    RULE(.class = "URxvt", .isterminal = 1)
    RULE(.class = "St", .isterminal = 1)
    RULE(.class = "Sxiv", .isfloating = 1, .iscentered = 1)
    RULE(.instance = "sx_", .isfloating = 1, .iscentered = 0)
    RULE(.instance = "sxview", .isfloating = 0, .iscentered = 0)
    RULE(.class = "Mullvad VPN", .isfloating = 1, .iscentered =1)
    RULE(.class = "Signal", .isfloating = 1, .iscentered = 1)
    // RULE(.class = "Galculator", .isfloating = 1, .iscentered = 1)
    RULE(.instance = "urxvtfloat", .isfloating = 1, .iscentered = 1, .isterminal = 1)
    RULE(.instance = "urxvtncmpcpp", .isfloating = 1, .iscentered = 1)
};

static const MonitorRule monrules[] = {
	/* monitor  tag   layout  mfact  nmaster  showbar  topbar */
	{  1,       -1,   2,      -1,    -1,      -1,      -1     }, // use a different layout for the second monitor
	{  -1,      -1,   0,      -1,    -1,      -1,      -1     }, // default
};

static const Inset default_inset = {
	.x = 0,
	.y = 54,
	.w = 0,
	.h = 0,
};

/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = { { -2 } };

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int nstack      = 0;    /* number of clients in primary stack area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */


static const Layout layouts[] = {
	/* symbol     arrange function, { nmaster,  nstack, layout,                     master axis,    stack axis,     secondary stack axis,   symbol func } */
	{ "",      flextile,           { -1,       -1,     SPLIT_VERTICAL,             TOP_TO_BOTTOM,  TOP_TO_BOTTOM,  0,                      NULL } },   // tile
	{ "",      flextile,           { -1,       -1,     NO_SPLIT,                   MONOCLE,        MONOCLE,        0,                      NULL } },   // monocle
 	// { "",      NULL,               {0} },                                                                                                              // float
/* { "|||",      flextile,        { -1,       -1,     SPLIT_VERTICAL,             LEFT_TO_RIGHT,  TOP_TO_BOTTOM,  0,                      NULL } },   // columns (col) layout */
 // { "",      flextile,        { -1,       -1,     FLOATING_MASTER,            LEFT_TO_RIGHT,  GAPPLESSGRID,  0,                      NULL } },   // floating master */
/* { "[D]",      flextile,        { -1,       -1,     SPLIT_VERTICAL,             TOP_TO_BOTTOM,  MONOCLE,        0,                      NULL } },   // deck */
/* { "TTT",      flextile,        { -1,       -1,     SPLIT_HORIZONTAL,           LEFT_TO_RIGHT,  LEFT_TO_RIGHT,  0,                      NULL } },   // bstack */
/* { "===",      flextile,        { -1,       -1,     SPLIT_HORIZONTAL,           LEFT_TO_RIGHT,  TOP_TO_BOTTOM,  0,                      NULL } },   // bstackhoriz */
	// { "",      flextile,           { -1,       -1,     SPLIT_CENTERED_VERTICAL,    LEFT_TO_RIGHT,  TOP_TO_BOTTOM,  TOP_TO_BOTTOM,          NULL } },   // centeredmaster
	// { "",      flextile,           { -1,       -1,     SPLIT_CENTERED_HORIZONTAL,  TOP_TO_BOTTOM,  LEFT_TO_RIGHT,  LEFT_TO_RIGHT,          NULL } },   // centeredmaster horiz
	// { "",      flextile,           { -1,       -1,     NO_SPLIT,                   GAPPLESSGRID,   GAPPLESSGRID,   0,                      NULL } },   // gappless grid
	/* { "[\\]",     flextile,      { -1,       -1,     NO_SPLIT,                   DWINDLE,        DWINDLE,        0,                      NULL } },   // fibonacci dwindle */
	/* { "(@)",      flextile,      { -1,       -1,     NO_SPLIT,                   SPIRAL,         SPIRAL,         0,                      NULL } },   // fibonacci spiral */
	/* { "[T]",      flextile,      { -1,       -1,     SPLIT_VERTICAL,             LEFT_TO_RIGHT,  TATAMI,         0,                      NULL } },   // tatami mats */
	/* { NULL,       NULL,          {0} }, */
};


/* key definitions */
#define modkey  Mod4Mask
#define shift   ShiftMask
#define ctrl    ControlMask
#define alt     Mod1Mask


#define TAGKEYS(KEY,TAG) \
	{ modkey,             KEY,      view,           {.ui = 1 << TAG} }, \
	{ modkey|ctrl,        KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ modkey|shift,       KEY,      tag,            {.ui = 1 << TAG} }, \
	{ modkey|ctrl|shift,  KEY,      toggletag,      {.ui = 1 << TAG} },


/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
	"dmenu_run",
	"-m", dmenumon,
	"-fn", dmenufont,
	"-nb", normbgcolor,
	"-nf", normfgcolor,
	"-sb", selbgcolor,
	"-sf", selfgcolor,
	NULL
};
/* static const char *termcmd[]  = { "st", NULL }; */


static Key keys[] = {
    /* modifier     key         func.   argument                              */
    /* apps ----------------------------------------------------------------- */
    { modkey,       XK_Return,  spawn,                  SHCMD("urxvtc") },
    { modkey|shift, XK_Return,  spawn,                  SHCMD("toggle urxvtfloat") },
    { modkey|ctrl,  XK_Return,  spawn,                  SHCMD("st") },
    { modkey,       XK_d,       spawn,                  SHCMD("dm_run") },
    { modkey,       XK_Print,   spawn,                  SHCMD("screenshot") },
    { modkey|shift, XK_Print,   spawn,                  SHCMD("scrot") },
    { modkey,       XK_F1,      spawn,                  SHCMD("toggle firefoxone") },
    { modkey,       XK_F2,      spawn,                  SHCMD("toggle FreeTube") },
    // { modkey,       XK_F2,      spawn,                  SHCMD("toggle firefoxtwo") },
    { modkey,       XK_F3,      spawn,                  SHCMD("toggle chromium") },
    { modkey,       XK_F4,      spawn,                  SHCMD("thunderbird") },
    { modkey,       XK_F5,      spawn,                  SHCMD("steam -forcedesktopscaling 1.5") },
    // { modkey,       XK_F5,      spawn,                  SHCMD("steam-screensaver-fix") },
    { modkey,       XK_f,       spawn,                  SHCMD("pcmanfm") },
    { modkey|shift, XK_f,       spawn,                  SHCMD("st -e lfrun") },
    { modkey,       XK_h,       spawn,                  SHCMD("dm_headphone") },
    { modkey,       XK_k,       spawn,                  SHCMD("toggle keepassxc") },
    { modkey,       XK_n,       spawn,                  SHCMD("toggle urxvtncmpcpp") },
    { modkey|shift, XK_n,       spawn,                  SHCMD("dm_notflix") },
    { modkey,       XK_m,       spawn,                  SHCMD("dm_mobile_sync") },
    { modkey|shift, XK_m,       spawn,                  SHCMD("sx_movies") },
    // { modkey,       XK_p,       spawn,                  SHCMD("pamac-manager") },
    { modkey,                   XK_p,                   togglefloating, {0} },
    { modkey|shift,             XK_p,                   togglesticky, {0} },
    { modkey,       XK_q,       spawn,                  SHCMD("dm_history") },
    { modkey,       XK_e,       spawn,                  SHCMD("dm_edit") },
    { modkey|shift, XK_e,       spawn,                  SHCMD("dm_dox") },
    { modkey,       XK_r,       spawn,                  SHCMD("dm_redshift") },
    // { modkey,       XK_s,       spawn,                  SHCMD("sx_steam") },
    { modkey,       XK_s,       spawn,                  SHCMD("dm_search") },
    // { modkey|shift, XK_s,       spawn,                  SHCMD("toggle signal") },
    // { modkey|ctrl,  XK_s,       spawn,                  SHCMD("sx_retroarch") },
    { modkey,       XK_t,       spawn,                  SHCMD("dm_translate") },
    { modkey|shift, XK_t,       spawn,                  SHCMD("dm_docs todo") },
    { modkey,       XK_u,       spawn,                  SHCMD("dm_umlaute") },
    { modkey,       XK_v,       spawn,                  SHCMD("toggle vpn") },
    { modkey,       XK_w,       spawn,                  SHCMD("cmen") },
    { modkey,       XK_F11,     spawn,                  SHCMD("sx_wpg") },
    { modkey,       XK_a,       spawn,                  SHCMD("autofire on") },
    { modkey|shift, XK_a,       spawn,                  SHCMD("autofire off") },
    { modkey,       XK_b,       spawn,                  SHCMD("blueman-manager") },
    { modkey|shift, XK_b,       spawn,                  SHCMD("bt_reconnect") },
    { modkey,       XK_c,       spawn,                  SHCMD("dm_calculator") },
    { modkey|shift, XK_c,       spawn,                  SHCMD("dm_docs cheatsheet") },
    { modkey,       XK_x,       spawn,                  SHCMD("dm_clip") },
    { modkey,       XK_y,       spawn,                  SHCMD("dm_youtube") },
    { modkey|shift, XK_y,       spawn,                  SHCMD("sx_youtube") },
    { modkey,       XK_0,       spawn,                  SHCMD("dm_system_menu") },
    { modkey|shift, XK_0,       spawn,                  SHCMD("game_close") },
    /* wm ------------------------------------------------------------------- */
    { modkey|shift, XK_w,       killclient,             {0} },
    { modkey,       XK_Tab,     zoom,                   {0} },
    { modkey,       XK_F10,     xrdb,                   {.v = NULL } },         // xrdb merge
    { modkey,       XK_F12,     quit,                   {1} },                  // reload dwm
    { modkey|shift, XK_F12,     quit,                   {0} },                  // quit dwm
    { modkey,       XK_g,       setlayout,              {.v = &layouts[1]} },
    { modkey|shift, XK_g,       togglefullscreen,       {0} },
    { modkey|ctrl,  XK_g,       togglefakefullscreen,   {0} },
    { modkey,       XK_Left,    focusdir,               {.i = 0 } }, // left
    { modkey,       XK_Right,   focusdir,               {.i = 1 } }, // right
    { modkey,       XK_Up,      focusdir,               {.i = 2 } }, // up
    { modkey,       XK_Down,    focusdir,               {.i = 3 } }, // down
    { modkey|shift, XK_Left,    setmfact,               {.f = -0.05} },
    { modkey|shift, XK_Right,   setmfact,               {.f = +0.05} },
    { modkey|shift, XK_Up,      setcfact,               {.f = +0.25} },
    { modkey|shift, XK_Down,    setcfact,               {.f = -0.25} },
    { modkey|alt,   XK_Left,    incnmaster,             {.i = +1 } },
    { modkey|alt,   XK_Right,   incnmaster,             {.i = -1 } },
    // { modkey|shift, XK_j,       shiftview,              { .i = -1 } }, // move left through tags
    // { modkey|shift, XK_k,       shiftview,              { .i = +1 } }, // move right through tags
    // { modkey|shift, XK_h,       shiftviewclients,       { .i = -1 } }, // move left through occupied tags
    // { modkey|shift, XK_l,       shiftviewclients,       { .i = +1 } }, // move right through occupied tags
    // { modkey|shift, XK_j,    viewtoleft,             {0} },
    // { modkey|shift, XK_k,   viewtoright,            {0} },
    { modkey|shift, XK_j,       rotatestack,            {.i = +1 } },
    { modkey|shift, XK_k,       rotatestack,            {.i = -1 } },
    /* { modkey|ctrl,               XK_i,            incnstack,             {.i = +1 } }, */
    /* { modkey|ctrl,               XK_u,            incnstack,             {.i = -1 } }, */
    /* { modkey|ctrl,               XK_Left,         tagtoleft,             {0} }, */
    /* { modkey|ctrl,               XK_Right,        tagtoright,            {0} }, */
    /* { modkey,                    XK_b,            togglebar,             {0} }, */
    // { modkey|shift,                    XK_j,            focusstack,            {.i = +1 } },
    // { modkey|shift,                    XK_k,            focusstack,            {.i = -1 } },
    /* { modkey|shift,              XK_o,            setcfact,              {0} }, */
    /* { modkey|Mod4Mask,           XK_Down,         moveresize,            {.v = "0x 25y 0w 0h" } }, */
    /* { modkey|Mod4Mask,           XK_Up,           moveresize,            {.v = "0x -25y 0w 0h" } }, */
    /* { modkey|Mod4Mask,           XK_Right,        moveresize,            {.v = "25x 0y 0w 0h" } }, */
    /* { modkey|Mod4Mask,           XK_Left,         moveresize,            {.v = "-25x 0y 0w 0h" } }, */
    /* { modkey|Mod4Mask|shift,     XK_Down,         moveresize,            {.v = "0x 0y 0w 25h" } }, */
    /* { modkey|Mod4Mask|shift,     XK_Up,           moveresize,            {.v = "0x 0y 0w -25h" } }, */
    /* { modkey|Mod4Mask|shift,     XK_Right,        moveresize,            {.v = "0x 0y 25w 0h" } }, */
    /* { modkey|Mod4Mask|shift,     XK_Left,         moveresize,            {.v = "0x 0y -25w 0h" } }, */
    /* { modkey|shift,              XK_j,            movestack,             {.i = +1 } }, */
    /* { modkey|shift,              XK_k,            movestack,             {.i = -1 } }, */
    /* { modkey|shift|ctrl,         XK_a,            updateinset,           {.v = &default_inset } }, */
    /* { modkey|Mod4Mask,           XK_u,            incrgaps,              {.i = +1 } }, */
    /* { modkey|Mod4Mask|shift,     XK_u,            incrgaps,              {.i = -1 } }, */
    /* { modkey|Mod4Mask,           XK_i,            incrigaps,             {.i = +1 } }, */
    /* { modkey|Mod4Mask|shift,     XK_i,            incrigaps,             {.i = -1 } }, */
    /* { modkey|Mod4Mask,           XK_o,            incrogaps,             {.i = +1 } }, */
    /* { modkey|Mod4Mask|shift,     XK_o,            incrogaps,             {.i = -1 } }, */
    /* { modkey|Mod4Mask,           XK_6,            incrihgaps,            {.i = +1 } }, */
    /* { modkey|Mod4Mask|shift,     XK_6,            incrihgaps,            {.i = -1 } }, */
    /* { modkey|Mod4Mask,           XK_7,            incrivgaps,            {.i = +1 } }, */
    /* { modkey|Mod4Mask|shift,     XK_7,            incrivgaps,            {.i = -1 } }, */
    /* { modkey|Mod4Mask,           XK_8,            incrohgaps,            {.i = +1 } }, */
    /* { modkey|Mod4Mask|shift,     XK_8,            incrohgaps,            {.i = -1 } }, */
    /* { modkey|Mod4Mask,           XK_9,            incrovgaps,            {.i = +1 } }, */
    /* { modkey|Mod4Mask|shift,     XK_9,            incrovgaps,            {.i = -1 } }, */
    /* { modkey|Mod4Mask,           XK_0,            togglegaps,            {0} }, */
    /* { modkey|Mod4Mask|shift,     XK_0,            defaultgaps,           {0} }, */
    /* { modkey,                    XK_Tab,          view,                  {0} }, */
    /* { modkey,                    XK_t,            setlayout,             {.v = &layouts[0]} }, */
    /* { modkey,                    XK_f,            setlayout,             {.v = &layouts[1]} }, */
    /* { modkey|ctrl,               XK_t,            rotatelayoutaxis,      {.i = +1 } },   /1* flextile, 1 = layout axis *1/ */
    /* { modkey|ctrl,               XK_Tab,          rotatelayoutaxis,      {.i = +2 } },   /1* flextile, 2 = master axis *1/ */
    /* { modkey|ctrl|shift,         XK_Tab,          rotatelayoutaxis,      {.i = +3 } },   /1* flextile, 3 = stack axis *1/ */
    /* { modkey|ctrl|alt,           XK_Tab,          rotatelayoutaxis,      {.i = +4 } },   /1* flextile, 4 = secondary stack axis *1/ */
    /* { modkey|Mod5Mask,           XK_t,            rotatelayoutaxis,      {.i = -1 } },   /1* flextile, 1 = layout axis *1/ */
    /* { modkey|Mod5Mask,           XK_Tab,          rotatelayoutaxis,      {.i = -2 } },   /1* flextile, 2 = master axis *1/ */
    /* { modkey|Mod5Mask|shift,     XK_Tab,          rotatelayoutaxis,      {.i = -3 } },   /1* flextile, 3 = stack axis *1/ */
    /* { modkey|Mod5Mask|alt,       XK_Tab,          rotatelayoutaxis,      {.i = -4 } },   /1* flextile, 4 = secondary stack axis *1/ */
    /* { modkey|ctrl,               XK_Return,       mirrorlayout,          {0} },          /1* flextile, flip master and stack areas *1/ */
    /* { modkey,                    XK_space,        setlayout,             {0} }, */
    /* { modkey|shift,              XK_Escape,       togglenomodbuttons,    {0} }, */
    /* { modkey|Mod4Mask,           XK_space,        unfloatvisible,        {0} }, */
    /* { modkey|shift,              XK_t,            unfloatvisible,        {.v = &layouts[0]} }, */
    /* { modkey|shift,              XK_f,            fullscreen,            {0} }, */
    /* { modkey,                    XK_0,            view,                  {.ui = ~0 } }, */
    /* { modkey|shift,              XK_0,            tag,                   {.ui = ~0 } }, */
    /* { modkey,                    XK_comma,        focusmon,              {.i = -1 } }, */
    /* { modkey,                    XK_period,       focusmon,              {.i = +1 } }, */
    /* { modkey|shift,              XK_comma,        tagmon,                {.i = -1 } }, */
    /* { modkey|shift,              XK_period,       tagmon,                {.i = +1 } }, */
    /* { modkey|shift,              XK_Left,         tagtoleft,             {0} }, */
    /* { modkey|shift,              XK_Right,        tagtoright,            {0} }, */
    /* { modkey|ctrl,               XK_Left,         tagandviewtoleft,      {0} }, */
    /* { modkey|ctrl,               XK_Right,        tagandviewtoright,     {0} }, */
    /* { modkey|ctrl,               XK_minus,        setborderpx,           {.i = -1 } }, */
    /* { modkey|ctrl,               XK_plus,         setborderpx,           {.i = +1 } }, */
    /* { modkey|ctrl,               XK_numbersign,   setborderpx,           {.i = 0 } }, */
    /* { modkey|ctrl,               XK_comma,        cyclelayout,           {.i = -1 } }, */
    /* { modkey|ctrl,               XK_period,       cyclelayout,           {.i = +1 } }, */
    TAGKEYS(                    XK_1,                                  0)
    TAGKEYS(                    XK_2,                                  1)
    TAGKEYS(                    XK_3,                                  2)
    TAGKEYS(                    XK_4,                                  3)
    TAGKEYS(                    XK_5,                                  4)
    TAGKEYS(                    XK_6,                                  5)
    TAGKEYS(                    XK_7,                                  6)
    TAGKEYS(                    XK_8,                                  7)
    TAGKEYS(                    XK_9,                                  8)
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask           button          function        argument */
	/* { ClkLtSymbol,          0,                   Button1,        setlayout,      {0} }, */
	/* { ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[2]} }, */
	/* { ClkWinTitle,          0,                   Button2,        zoom,           {0} }, */
	/* { ClkStatusText,        0,                   Button2,        spawn,          {.v = termcmd } }, */
	// { ClkRootWin,           0,                  Button4,        spawn,    SHCMD("dwm_view_direction up") },
	// { ClkRootWin,           0,                  Button5,        spawn,    SHCMD("dwm_view_direction down") },
	{ ClkRootWin,           0,                  Button4,        viewtoleft,     {0} },
	{ ClkRootWin,           0,                  Button5,        viewtoright,    {0} },
	{ ClkRootWin,           0,                  Button1,        spawn,          SHCMD("dwm_launch_on_tag") },
	{ ClkRootWin,           0,                  Button2,        dragmfact,      {0} },
	{ ClkRootWin,           0,                  Button3,        dragcfact,      {0} },
	{ ClkRootWin,           0,                  Button9,        zoom,    {0} },
	{ ClkRootWin,           0,                  Button8,        spawn,          SHCMD("pcmanfm") },
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
	 *    2 - mouse pointer warps to window center
	 *
	 * The moveorplace uses movemouse or placemouse depending on the floating state
	 * of the selected client. Set up individual keybindings for the two if you want
	 * to control these separately (i.e. to retain the feature to move a tiled window
	 * into a floating position).
	 */
	{ ClkClientWin,         modkey,            Button1,        moveorplace,    {.i = 1} },
	{ ClkClientWin,         modkey,            Button2,        togglefloating, {0} },
	{ ClkClientWin,         modkey,            Button3,        resizemouse,    {0} },
	{ ClkClientWin,         modkey|shift,      Button3,        dragcfact,      {0} },
	{ ClkClientWin,         modkey|shift,      Button1,        dragmfact,      {0} },
	/* { ClkTagBar,            0,              Button1,        view,           {0} }, */
	/* { ClkTagBar,            0,              Button3,        toggleview,     {0} }, */
	/* { ClkTagBar,            modkey,            Button1,        tag,            {0} }, */
	/* { ClkTagBar,            modkey,            Button3,        toggletag,      {0} }, */
};


static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
	IPCCOMMAND( focusmon, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( focusstack, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incnmaster, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( killclient, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( quit, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( setlayoutsafe, 1, {ARG_TYPE_PTR} ),
	IPCCOMMAND( setmfact, 1, {ARG_TYPE_FLOAT} ),
	IPCCOMMAND( setstatus, 1, {ARG_TYPE_STR} ),
	IPCCOMMAND( tag, 1, {ARG_TYPE_UINT} ),
	IPCCOMMAND( tagmon, 1, {ARG_TYPE_UINT} ),
	IPCCOMMAND( togglebar, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( togglefloating, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( toggletag, 1, {ARG_TYPE_UINT} ),
	IPCCOMMAND( toggleview, 1, {ARG_TYPE_UINT} ),
	IPCCOMMAND( view, 1, {ARG_TYPE_UINT} ),
	IPCCOMMAND( zoom, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( setcfact, 1, {ARG_TYPE_FLOAT} ),
	IPCCOMMAND( cyclelayout, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( togglefakefullscreen, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( fullscreen, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( incnstack, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( rotatelayoutaxis, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( setlayoutaxisex, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( mirrorlayout, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( viewtoleft, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( viewtoright, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( tagtoleft, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( tagtoright, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( tagandviewtoleft, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( tagandviewtoright, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( moveresize, 1, {ARG_TYPE_STR} ),
	IPCCOMMAND( rotatestack, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( setborderpx, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( shiftview, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( shiftviewclients, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( togglesticky, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( togglefullscreen, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( unfloatvisible, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( incrgaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incrigaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incrogaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incrihgaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incrivgaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incrohgaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( incrovgaps, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( togglegaps, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( defaultgaps, 1, {ARG_TYPE_NONE} ),
	IPCCOMMAND( setgapsex, 1, {ARG_TYPE_SINT} ),
	IPCCOMMAND( xrdb, 1, {ARG_TYPE_NONE} ),
};

