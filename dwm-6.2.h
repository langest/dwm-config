/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Ubuntu:size=14", "Kochi Mincho:size=14" };
static const char dmenufont[]       = "Ubuntu:size=14";

/* default colors
static const char norm_bg[]      = "#222222";
static const char norm_border[]  = "#444444";
static const char norm_fg[]      = "#bbbbbb";
static const char sel_fg[]       = "#eeeeee";
static const char sel_bg[]       = "#005577";
*/

/* gruvbox theme
 *
 * sel_bg options
 * #cc241d" red
 * #98971a" green
 * #458588" blue
 * #b16286" magenta
 */
static const char norm_bg[]      = "#928374";
static const char norm_fg[]      = "#282828";
static const char norm_border[]  = "#282828";
static const char sel_bg[]       = "#282828";
static const char sel_fg[]       = "#ebdbb2";
static const char sel_border[]   = "#98971a";

// windows 95
//static const char norm_bg[]      = "#c0c0c0";
//static const char norm_border[]  = "#808080";
//static const char norm_fg[]      = "#000000";
//
//static const char sel_fg[]       = "#ffffff";
//static const char sel_bg[]       = "#000da6";
//static const char sel_border[]   = "#000da6";

static const char *colors[][3]      = {
	/*               fg       bg       border   */
	[SchemeNorm] = { norm_fg, norm_bg, norm_border },
	[SchemeSel]  = { sel_fg,  sel_bg,  sel_border  },
};

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class       instance title tags mask isfloating monitor */
	{ "Gimp",      NULL,    NULL, 0,        0,         -1 },
	{ "KeePassXC", NULL,    NULL, 1 << 6,   0,          0 },
	{ "Chromium",  NULL,    NULL, 1 << 7,   0,          0 },
	{ "Firefox",   NULL,    NULL, 1 << 8,   0,          1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", norm_bg, "-nf", norm_fg, "-sb", sel_bg, "-sf", sel_fg, NULL };
static const char *termcmd[]     = { "st", NULL };
static const char *firefoxcmd[]  = { "firefox", NULL };
static const char *chromiumcmd[] = { "chromium", NULL };
static const char *lockcmd[]     = { "slock", NULL };
/*
static const char *mpdPrev[]      = { "mpc", "prev", NULL };
static const char *mpdNext[]      = { "mpc", "next", NULL };
static const char *mpdPlayPause[] = { "mpc", "toggle", NULL };
static const char *mpdPlayStop[]  = { "mpc", "stop", NULL };
*/
static const char *random_wp_fill[]     = { "feh", "--randomize", "--recursive", "--bg-fill", "/home/langest/img/wps/", NULL };
static const char *random_wp_tile[]     = { "feh", "--randomize", "--recursive", "--bg-tile", "/home/langest/img/tiling/", NULL };

static const char *hdmiOff[]      = { "xrandr", "--output", "HDMI2", "--off", NULL };
static const char *hdmiMirror[]   = { "xrandr", "--output", "HDMI2", "--same-as", "LVDS1", "--mode", "1280x800", NULL };
static const char *hdmiAbove[]    = { "xrandr", "--output", "HDMI2", "--above", "LVDS1", "--auto", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	/* Launchers */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = firefoxcmd } },
	{ MODKEY|ShiftMask,             XK_g,      spawn,          {.v = chromiumcmd } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = lockcmd } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = random_wp_fill } },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = random_wp_tile } },

	/* Keyboard management */
	{ MODKEY|ShiftMask,             XK_u,      spawn,          SHCMD("setxkbmap us -option ctrl:nocaps && pkill dwmstatus -SIGUSR1") },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("setxkbmap se -option ctrl:nocaps && pkill dwmstatus -SIGUSR1") },

	/* Screen management */
	{ MODKEY|ShiftMask,             XK_F7,     spawn,          {.v = hdmiOff} },
	{ MODKEY|ShiftMask,             XK_F8,     spawn,          {.v = hdmiMirror} },
	{ MODKEY|ShiftMask,             XK_F9,     spawn,          {.v = hdmiAbove} },

	/* Special keys */
	{ 0,                       0x1008FF12,     spawn,          SHCMD("amixer set Master -c 0 0% && pkill dwmstatus -SIGUSR1") },
	{ 0,                       0x1008FF11,     spawn,          SHCMD("amixer set Master -c 0 unmute 2- -M && pkill dwmstatus -SIGUSR1") },
	{ 0,                       0x1008FF13,     spawn,          SHCMD("amixer set Master -c 0 unmute 2+ -M && pkill dwmstatus -SIGUSR1") },
	{ 0,                       0x1008FF02,     spawn,          SHCMD("xbacklight -inc 1 && pkill dwmstatus -SIGUSR2") },
	{ 0,                       0x1008FF03,     spawn,          SHCMD("xbacklight -dec 1 && pkill dwmstatus -SIGUSR2") },

	/* Window management */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_l,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_h,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_k,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_j,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask|ControlMask, XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

