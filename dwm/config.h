/* See LICENSE file for copyright and license details. */

/*	WHAT I CHANGED HERE:
	1. FONT CHANGED
	2. GAPS PATCH STUFF ADDED (COMMENTD TO AVOID COPY-PASTED BUILD ERROR!)
	3. CHANGED TAGS NAME
	4. ASSIGNED APPS TO THOSE TAG NAMES
	5. SET MASTER AREA TO HAVE THE SAME SIZE AS THE OTHER AREA!
	6. SET MONOCLE TO BE DEFAULT LAYOUT OPTION (PERSONAL PREFERENCE)
	7. MODEKEY SET TO SUPER/WINDOWS KEY
	8. ADDED DIFFERENT COMMANDS TO LAUNCH FREQUENT APPS AND ALSO XF86 KEYS FOR VOLUME(USING SCRIPT) AND BRIGHTNESS
	9. DEFINED KEYS TO RUN THOSE COMMANDS
*/

/* ENABLES XF86* KEYS */
#include <X11/XF86keysym.h>

/* appearance */
static const char *fonts[] = {
	"monofur nerd font mono:size=10"
};
static const char dmenufont[]       = "monofur nerd font mono:size=10";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
/* static const unsigned int gappx     = 0;        /* gaps between windows - WORKS ONLY WITH GAPS PATCH APPLIED */

/* tagging */
/* USING NAMES WITH NUMBERS IMPROVED MY SWITCHING SPEED */
static const char *tags[] = { "1.main", "2.browser", "3.code", "4.docs", "5.graphic", "6.files", "7.other", "8.media" };

/* I DIDNT REALLY UNDERSTOOD HOW THESE TAG MASKS WORKED */
/* SHOULD LEARN BINARY SHIFTING! */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                instance            title       tags mask     isfloating   monitor */
	{ "Firefox",            "Navigator",        NULL,       2,            0,           -1 },
	{ "Google-chrome",      "google-chrome",    NULL,       2,            0,           -1 },
	{ "Code",               "code",             NULL,       1 << 2,       0,           -1 },
	{ "Zathura",            NULL,               NULL,       1 << 3,       0,           -1 },
	{ "Gimp",               "gimp",             NULL,       1 << 4,       0,           -1 },
	{ "Thunar",             NULL,               NULL,       1 << 5,       0,           -1 },
	{ "mpv",                "gl",               NULL,       1 << 7,       0,           -1 }
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle }, /* I PREFER MONOCLE AS DEFAULT THEN I CHANGE TO TILES IF I WANT TO SEE THEM BOTH */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run_history", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *rofifb[]    	= { "rofi", "-modi", "fb:rofi-file-browser.sh", "-show", "fb" , NULL};
static const char *termcmd[]    = { "rxvt-unicode", NULL };
static const char *firefox[]    = { "firefox", NULL };
static const char *ranger[]     = { "rxvt-unicode", "-e", "ranger", NULL };
static const char *mocp[]       = { "rxvt-unicode", "-e", "mocp", NULL };
static const char *volup[]      = { "volnotif.sh", "up", NULL };
static const char *voldown[]    = { "volnotif.sh", "down", NULL };
static const char *volmute[]    = { "volnotif.sh", "toggle", NULL };
static const char *brightup[]   = { "brightnessctl", "set", "+10%", NULL };
static const char *brightdown[] = { "brightnessctl", "set", "10%-", NULL };

/*	ADD THESE LINES 
	TO THE LIST TO ENABLE GAPS RESIZEING
	ONLY AFTER APPLYING GAPS PATCH
*/ 
/*
    { MODKEY,                       XK_minus,                   setgaps,        {.i = -1 } },
    { MODKEY,                       XK_equal,                   setgaps,        {.i = +1 } },
    { MODKEY|ShiftMask,             XK_equal,                   setgaps,        {.i = 0  } },
*/

static Key keys[] = {
	/* modifier                     key                         function        argument */
	{ 0,                            XF86XK_AudioRaiseVolume,    spawn,          {.v = volup } },
	{ 0,                            XF86XK_AudioLowerVolume,    spawn,          {.v = voldown } },
	{ 0,                            XF86XK_AudioMute,           spawn,          {.v = volmute } },
	{ 0,                            XF86XK_MonBrightnessUp,     spawn,          {.v = brightup } },
	{ 0,                            XF86XK_MonBrightnessDown,   spawn,          {.v = brightdown } },
	{ MODKEY,                       XK_p,                       spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_o,                       spawn,          {.v = rofifb } },
	{ MODKEY|ShiftMask,             XK_Return,                  spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_f, 	                    spawn,          {.v = firefox } },
	{ MODKEY|ShiftMask,             XK_r, 	                    spawn,          {.v = ranger } },
	{ MODKEY|ShiftMask,             XK_m, 	                    spawn,          {.v = mocp } },
	{ MODKEY,                       XK_b,                       togglebar,      {0} },
	{ MODKEY,                       XK_Tab,                     focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,                     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                       incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                       incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                       setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                       setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,                  zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_c,                       killclient,     {0} },
	{ MODKEY,                       XK_t,                       setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                       setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                       setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                   setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                   togglefloating, {0} },
	{ MODKEY,                       XK_0,                       view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                       tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                  tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	{ MODKEY|ShiftMask,             XK_q,                       quit,           {0} },
};


/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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
