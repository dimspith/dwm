/* See LICENSE file for copyright and license details. */

/************************************/
/*            APPEARANCE            */
/************************************/

static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */

static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */

static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const char *fonts[]          = { "FiraMono Nerd Font:size=10:style=medium", "monospace:size=10" };
static const char dmenufont[]       = "FiraMono Nerd Font:size=10";


/************************************/
/*              COLORS              */
/************************************/

static const char col_fg[]             = "#f0f0f0";
static const char col_bg[]             = "#0f0f0f";
static const char col_fg_sel[]         = "#f0f0f0";
static const char col_bg_sel[]         = "#4c4c4c";
static const char col_border[]         = "#141413";
static const char col_border_sel[]     = "#9ec3c4";
static const char col_inact_fg[]       = "#cacaca";
static const char col_inact_bg[]       = "#0f0f0f";
static const char col_inact_border[]   = "#ac8aac";
static const char col_dmenu_h_fg[]     = "#9ec3c4";
static const char col_dmenu_h_bg[]     = "#0f0f0f";
static const char col_dmenu_h_sel_fg[] = "#9ec3c4";
static const char col_dmenu_h_sel_bg[] = "#4c4c4c";

static const char *colors[][3]           = {
    /*                       fg            bg               border   */
    [SchemeNorm]         = { col_fg,       col_bg,        col_border      },
    [SchemeSel]          = { col_fg_sel,   col_bg_sel,    col_border_sel  },
    [SchemeTabActive]    = { col_inact_fg, col_inact_bg,  col_inact_border  },
    [SchemeTabInactive]  = { col_inact_fg, col_inact_bg,  col_inact_border  }
};

/************************************/
/*        LAYOUTS/TAGS/RULES        */
/************************************/

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

/* tagging */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* Bartabgroups properties */
#define BARTAB_BORDERS 1       // 0 = off, 1 = on
#define BARTAB_BOTTOMBORDER 0  // 0 = off, 1 = on
#define BARTAB_TAGSINDICATOR 1 // 0 = off, 1 = on if >1 client/view tag, 2 = always on
#define BARTAB_TAGSPX 5        // # pixels for tag grid boxes
#define BARTAB_TAGSROWS 3      // # rows in tag grid (9 tags, e.g. 3x3)
static void (*bartabmonfns[])(Monitor *) = { monocle /* , customlayoutfn */ };
static void (*bartabfloatfns[])(Monitor *) = { NULL /* , customlayoutfn */ };

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "~Tile~",       tile },    /* first entry is default */
    { "~Float~",      NULL },    /* no layout function means floating behavior */
    { "~Monocle~",    monocle },
    { "~Deck~",       deck }
};

static const Rule rules[] = {
    /* class           instance    title                        tags mask  isfloating  monitor */
    { "Element",         NULL,     NULL,                        1 << 3,    0,          -1 },
    { "strawberry",      NULL,     NULL,                        1 << 5,    0,          -1 },
    { "Steam",           NULL,     NULL,                        1 << 4,    0,          -1 },
    { "qBittorrent",     NULL,     NULL,                        1 << 5,    0,          -1 },
    { "TelegramDesktop", NULL,     NULL,                        1 << 3,    0,          -1 },
    { "discord",         NULL,     NULL,                        1 << 3,    0,          -1 },
    { "Discord",         NULL,     NULL,                        1 << 3,    0,          -1 },
    { "element",         NULL,     NULL,                        1 << 3,    0,          -1 },
    { "Element",         NULL,     NULL,                        1 << 3,    0,          -1 },

};

/************************************/
/*          KEYS/COMMANDS           */
/************************************/

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
static const char *dmenucmd[]   = { "dmenu_run",
                                    "-p",  "Run: ",
                                    "-fn",  dmenufont,
                                    "-nb",  col_bg,
                                    "-nf",  col_fg,
                                    "-sb",  col_bg_sel,
                                    "-sf",  col_fg_sel,
                                    "-hf",  col_dmenu_h_fg,
                                    "-hb",  col_dmenu_h_bg,
                                    "-shf", col_dmenu_h_sel_fg,
                                    "-shb", col_dmenu_h_sel_bg,
                                    NULL };

static const char *termcmd[]    = { "alacritty", NULL };
static const char *editorcmd[]  = { "emacsclient", "-c", NULL };
static const char *progmenu[]   = { "rofi", "-show", "drun", NULL};
static const char *browsercmd[] = { "firefox", NULL };
static const char *fmcmd[]      = { "alacritty", "-e", "vifm", NULL };
static const char *wscmd[]      = { "rofi", "-show", "window", NULL };
static const char *scrotcmd[]   = { "flameshot", "gui", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */

    /* Program launching */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = progmenu } },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_b,      spawn,          {.v = browsercmd} },
    { MODKEY|ShiftMask,             XK_e,      spawn,          {.v = editorcmd} },
    { MODKEY|ShiftMask,             XK_f,      spawn,          {.v = fmcmd} },
    { Mod1Mask,                     XK_Tab,    spawn,          {.v = wscmd} },
    { 0,                            XK_Print,  spawn,          {.v = scrotcmd} },

    /* Window/Layout manipulation */
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_space,  focusmaster,    {0} },
    { MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
    { MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_u,      resetnmaster,   {0} },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY|ControlMask,           XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_d,      setlayout,      {.v = &layouts[3]} },
    { MODKEY|ControlMask,           XK_space,  setlayout,      {0} },
    { MODKEY,                       XK_f,      fullscreen,     {0} },
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
    { MODKEY|ShiftMask,             XK_r,      quit,           {0} },
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

