open Emotion;

let wrap = [%css
  [
    alignItems(`center),
    display(`flex),
    flexFlow(`column, `nowrap),
    padding(`px(50)),
  ]
];

let artist_holder = [%css
  [
    alignItems(`center),
    display(`flex),
    flexFlow(`row, `nowrap),
    marginBottom(`px(50)),
  ]
];

let artist_avatar = [%css
  [
    appearance(`none),
    cursor(`pointer),
    outlineStyle(`none),
    width(`px(96)),
    height(`px(96)),
    borderRadius(`px(96)),
    borderWidth(`px(0)),
    marginLeft(`px(25)),
    marginRight(`px(25)),
    transitionProperty("box-shadow"),
    transitionDuration(`ms(200)),
    transitionTimingFunction(`easeInOut),
    hover([
      boxShadow(~y=px(4), ~blur=px(12), `hsla((341, 100, 12, 0.1))),
    ]),
  ]
];

let artist_avatar_s = [%css
  [boxShadow(~y=px(4), ~blur=px(16), `hsla((341, 100, 12, 0.12)))]
];

let artist_avatar_selected = Cx.merge([|artist_avatar, artist_avatar_s|]);

let lyrics_holder = [%css
  [
    marginTop(`px(25)),
    color(`hex("FFF")),
    width(`px(392)),
    padding(`px(25)),
    lineHeight(`pct(150.)),
    fontStyle(`italic),
    fontSize(`px(18)),
    backgroundColor(`hex("FF0856")),
    borderRadius(`px(5)),
    boxShadow(~y=px(8), ~blur=px(32), `hsla((341, 100, 12, 0.28))),
  ]
];