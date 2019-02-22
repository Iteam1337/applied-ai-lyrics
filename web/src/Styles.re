open Emotion;

let wrap = [%css
  [
    alignItems(`center),
    display(`flex),
    flexFlow(`column, `nowrap),
    justifyContent(`center),
    height(`pct(100.0)),
    padding(`px(50)),
  ]
];

let artist_holder = [%css
  [
    alignItems(`center),
    display(`flex),
    flexFlow(`row, `nowrap),
    marginTop(`px(50)),
  ]
];

let artist_avatar = [%css
  [
    appearance(`none),
    borderRadius(`px(96)),
    borderWidth(`px(0)),
    boxShadow(~y=px(4), ~blur=px(12), `hsla((341, 100, 12, 0.05))),
    cursor(`pointer),
    height(`px(96)),
    marginLeft(`px(25)),
    marginRight(`px(25)),
    outlineStyle(`none),
    transitionDuration(`ms(150)),
    transitionProperty("box-shadow transform"),
    transitionTimingFunction(`easeIn),
    width(`px(96)),
    hover([
      boxShadow(~y=px(4), ~blur=px(12), `hsla((341, 100, 12, 0.1))),
    ]),
  ]
];

let artist_avatar_s = [%css
  [
    boxShadow(~y=px(4), ~blur=px(16), `hsla((341, 100, 12, 0.12))),
    transform(`scale(1.33)),
  ]
];

let artist_avatar_selected = Cx.merge([|artist_avatar, artist_avatar_s|]);

let button = [%css
  [
    alignItems(`center),
    appearance(`none),
    backgroundColor(`hex("FF0856")),
    borderRadius(`px(5)),
    boxShadow(~y=px(8), ~blur=px(32), `hsla((341, 100, 12, 0.28))),
    color(`hex("FFF")),
    cursor(`pointer),
    display(`flex),
    fontSize(`px(18)),
    height(`px(48)),
    justifyContent(`center),
    width(`px(164)),
  ]
];

let lyrics_wrap = [%css
  [alignItems(`center), display(`flex), flexDirection(`column)]
];

let lyrics_holder = [%css
  [
    backgroundColor(`hex("FF0856")),
    borderRadius(`px(24)),
    boxShadow(~y=px(8), ~blur=px(32), `hsla((341, 100, 12, 0.28))),
    color(`hex("FFF")),
    display(`flex),
    fontSize(`px(18)),
    fontStyle(`italic),
    lineHeight(`pct(150.)),
    marginTop(`px(25)),
    width(`px(512)),
  ]
];

let lyrics_text = [%css [padding(`px(25))]];

let lyrics_artist = [%css
  [
    color(`hex("FFE5EE")),
    display(`block),
    fontSize(`px(13)),
    fontStyle(`normal),
    fontWeight(700),
    letterSpacing(`px(1)),
    lineHeight(`pct(150.)),
    marginTop(`px(20)),
    textTransform(`uppercase),
  ]
];