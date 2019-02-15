module WrapperStyle = {
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
      hover([backgroundColor(`hex("FAFAFA"))]),
    ]
  ];

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
};

module Artist = {
  type artist =
    | Abba
    | Kendrick
    | Ledin
    | Maggio;

  type t = {name: string};

  let get_name = artist =>
    switch (artist) {
    | Abba => "Abba"
    | Kendrick => "Kendrick Lamar"
    | Ledin => "Tomas Ledin"
    | Maggio => "Veronica Maggio"
    };

  let get_endpoint = artist => {
    switch (artist) {
    | Abba => "abba"
    | Kendrick => "kendrick"
    | Ledin => "ledin"
    | Maggio => "maggio"
    };
  };

  let get_all = () => [Abba, Kendrick, Ledin, Maggio];
};

module Lyrics = {
  open Js.Promise;
  let get_lyrics = (artist: Artist.artist) => {
    Axios.get(
      "http://localhost:5000/api/generate/" ++ Artist.get_endpoint(artist),
    )
    |> then_(response => resolve(response));
  };
};

type state = {
  artist: Artist.artist,
  lyrics: option(string),
};

type action =
  | Artist(Artist.artist)
  | Generate
  | Loading
  | Generated(string);

let component = ReasonReact.reducerComponent("Wrapper");

let make = _children => {
  ...component,

  initialState: () => {artist: Kendrick, lyrics: None},

  reducer: (action, state) =>
    switch (action) {
    | Artist(a) => ReasonReact.Update({...state, artist: a})
    | Generate =>
      ReasonReact.SideEffects(
        self => {
          self.send(Loading);
          Js.Promise.(
            Lyrics.get_lyrics(self.state.artist)
            |> then_(res => {
                 self.send(Generated(res##data##data));
                 resolve();
               })
            |> ignore
          );
        },
      )
    | Generated(l) => ReasonReact.Update({...state, lyrics: Some(l)})
    | Loading => ReasonReact.NoUpdate
    },

  render: self => {
    <div className=WrapperStyle.wrap>
      <div className=WrapperStyle.artist_holder>
        {ReasonReact.array(
           Array.of_list(
             List.map(
               a =>
                 <button
                   className=WrapperStyle.artist_avatar
                   key={Artist.get_name(a)}
                   onClick={_event => self.send(Artist(a))}>
                   {Artist.get_name(a) |> ReasonReact.string}
                 </button>,
               Artist.get_all(),
             ),
           ),
         )}
      </div>
      {"Selected artist: " |> ReasonReact.string}
      {self.state.artist |> Artist.get_name |> ReasonReact.string}
      <button onClick={_event => self.send(Generate)}>
        {ReasonReact.string("Generate")}
      </button>
      {switch (self.state.lyrics) {
       | Some(l) =>
         <div className=WrapperStyle.lyrics_holder>
           {Belt.Option.getWithDefault(self.state.lyrics, "")
            |> ReasonReact.string}
         </div>
       | None => <div />
       }}
    </div>;
  },
};