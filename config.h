/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static char font[]            = "Source Code Pro:size=10";
/*static const char font[]  = "-wuncon-siji-medium-r-normal--10-100-75-75-c-80-iso10646-1" "," "-*-tamsyn-medium-r-normal-*-12-*-*-*-*-*-*-1";*/
/* For Iconic Glyphs */                  /* For Normal Text */
static char dmenufont[]       = "Source Code Pro:size=10";
/*static char font[]            = "monospace:size=10";*
*static char dmenufont[]       = "monospace:size=10";*/
static const char *fonts[]          = { font };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
/* red blue orange green pink  */
static char col1[]            = "#ffffff";
static char col2[]            = "#ed333b";
static char col3[]            = "#71c2ff";
static char col4[]            = "#ff9458";
static char col5[]            = "#56e39b";
static char col6[]            = "#ff628f";
/*static char col_urgborder[]   = "#ff0000";*/

enum { SchemeNorm, SchemeCol1, SchemeCol2, SchemeCol3, SchemeCol4,
       SchemeCol5, SchemeCol6, SchemeSel, SchemeUrg }; /* color schemes */

static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
	[SchemeUrg]  = { selfgcolor,  selbgcolor,  selbordercolor },
	[SchemeCol1]  = { col1,      normbgcolor, normbordercolor },
	[SchemeCol2]  = { col2,      normbgcolor, normbordercolor },
	[SchemeCol3]  = { col3,      normbgcolor, normbordercolor },
	[SchemeCol4]  = { col4,      normbgcolor, normbordercolor },
	[SchemeCol5]  = { col5,      normbgcolor, normbordercolor },
	[SchemeCol6]  = { col6,      normbgcolor, normbordercolor },
};

static const char *const autostart[] = {
/*	"firefox", NULL, */
/*	"wps", NULL, */
/*	"sh","-c","sleep 10 && ~/.nutstore/dist/bin/nutstore-pydaemon.py &",NULL,*/
	/*"sh","-c","slstatus&",NULL,*/
	/*"zsh","-c","sleep 10 ; case $(cat /etc/issue | cut -d " " -f1) { (Arch)  picom & ;; (Ubuntu) compton & ;; }",NULL,*/
	"zsh","-c","${HOME}/.config/dwm/dwmrc.zsh",NULL,
	"sh","-c","while :; do feh --randomize --bg-fill ~/Pictures/wallpaper/*.jpg; sleep 600; done &",NULL,
	"sh","-c","sleep 10 && ibus-daemon --xim -d ",NULL,
	"st", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "wps",      NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Thunar",   NULL,       NULL,       5,       0,           -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask/*mod1 alt mod2 Numlock mod4 win*/
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
/* https://cgit.freedesktop.org/xorg/proto/x11proto/tree/XF86keysym.h */
#define XF86XK_AudioLowerVolume	0x1008FF11   /* Volume control down        */
#define XF86XK_AudioMute	0x1008FF12   /* Mute sound from the system */
#define XF86XK_AudioRaiseVolume	0x1008FF13   /* Volume control up          */ 

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
<<<<<<< HEAD
<<<<<<< HEAD

<<<<<<< HEAD
static const Key keys[] = {
=======
=======
static const char *raisevolume[] = {"sh","-c","amixer set Master '3+'",NULL};
static const char *mutevolume[] = {"sh","-c","amixer set Master toggle",NULL};
/* static const char *mutevolume[] = {"sh","-c","if [ $(amixer get Master | tail -n1 |cut -d [ -f4 | tr -d ]) == 'off' ];then;amixer set Master unmute;else;amixer set Master mute;fi",NULL}; */
static const char *lowervolume[] = {"sh","-c","amixer set Master '3-'",NULL};
<<<<<<< HEAD
>>>>>>> 0106633 (bindsym XF86XK_Audio**)
=======
=======
static const char *raisevolume[] = {"sh","-c","pactl set-sink-volume 0 +3%",NULL};
static const char *mutevolume[] = {"sh","-c"," pactl set-sink-mute 0 toggle ",NULL};
static const char *lowervolume[] = {"sh","-c","pactl set-sink-volume 0 -3%",NULL};
>>>>>>> 2633df8 (my dwm)
static const char *slockcmd[] = { "slock", NULL };
>>>>>>> d63303a (bindsym win(Mod4Mask)+l slock)
/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "font",               STRING,  &font },
		{ "dmenufont",          STRING,  &dmenufont },
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};

static Key keys[] = {
>>>>>>> 84c6b22 (patch xresources)
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
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
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ 0,             XF86XK_AudioLowerVolume,  spawn,          {.v = lowervolume }},
	{ 0,             XF86XK_AudioRaiseVolume,  spawn,          {.v = raisevolume }},
	{ 0,             XF86XK_AudioMute,  spawn,          {.v = mutevolume }},
	{ Mod1Mask,                     XK_l,      spawn,          {.v = slockcmd }},

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
};

