module Styles = {
  open Emotion;

  let wrap = [%css
    [
      alignItems(`center),
      display(`flex),
      flexFlow(`column, `nowrap),
      justifyContent(`flexStart),
      height(`vh(100.0)),
    ]
  ];

  let artist_holder = [%css
    [
      alignItems(`center),
      display(`flex),
      flexFlow(`row, `nowrap),
      flexGrow(1.0),
      paddingTop(`px(48)),
    ]
  ];

  let header_wrap = [%css [display(`flex), padding2(`px(64), `px(148))]];

  let text_wrap = [%css
    [
      alignItems(`flexStart),
      display(`flex),
      flexBasis(`pct(80.0)),
      flexDirection(`column),
    ]
  ];

  let image_wrap = [%css
    [
      alignItems(`center),
      display(`flex),
      flexBasis(`pct(20.0)),
      justifyContent(`center),
    ]
  ];

  let image_iteam = [%css [width(`px(320))]];

  let h1 = [%css
    [
      color(`hex("FF3373")),
      fontSize(`px(48)),
      lineHeight(`pct(120.0)),
      marginBottom(`px(56)),
    ]
  ];

  let paragraph = [%css
    [
      color(`hex("800028")),
      fontSize(`px(24)),
      lineHeight(`pct(150.0)),
      margin3(`px(0), `px(0), `px(32)),
    ]
  ];
};

type state = {artist: option(Artist.artist)};

type action =
  | SelectArtist(Artist.artist);

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _children => {
  ...component,

  initialState: () => {artist: None},

  reducer: (action, _state) =>
    switch (action) {
    | SelectArtist(a) => ReasonReact.Update({artist: Some(a)})
    },

  render: self => {
    <div className=Styles.wrap>
      <div className=Styles.header_wrap>
        <div className=Styles.text_wrap>
          <h1 className=Styles.h1>
            {{j|Hur kan det se ut när en AI genererar låttexter?|j}
             |> ReasonReact.string}
          </h1>
          <p className=Styles.paragraph>
            {{j|Här har vi tränat ett AI på ett antal av texterna från artisterna nedan.|j}
             |> ReasonReact.string}
          </p>
          <p className=Styles.paragraph>
            {{j|Varje artist genererar låttexter utifrån sin egna upptränade modell.|j}
             |> ReasonReact.string}
          </p>
          <p className=Styles.paragraph>
            {{j|Klicka på en artist och se vad du får för resultat!|j}
             |> ReasonReact.string}
          </p>
        </div>
        <div className=Styles.image_wrap>
          <img alt="Iteam" className=Styles.image_iteam src=Utils.iteam_i />
        </div>
      </div>
      <div className=Styles.artist_holder>
        {ReasonReact.array(
           Array.of_list(
             Artist.get_all()
             |> List.mapi((i, a) =>
                  <Avatar
                    key={Artist.get_name(a)}
                    artist=a
                    left={i > 2}
                    onClick={_event => self.send(SelectArtist(a))}
                    selected={
                      switch (self.state.artist) {
                      | Some(artist) =>
                        artist === a ? `Selected : `Not_selected
                      | None => `Not_selected
                      }
                    }
                  />
                ),
           ),
         )}
      </div>
    </div>;
  },
};
