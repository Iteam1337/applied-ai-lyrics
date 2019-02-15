module Api = {
  open Js.Promise;
  let get_lyrics = (artist: Artist.artist) => {
    Axios.get(
      "http://localhost:5000/api/generate/" ++ Artist.get_endpoint(artist),
    )
    |> then_(response => resolve(response));
  };
};

type lyricsState =
  | Idle
  | Loading
  | Lyrics(string);

type state = {
  artist: Artist.artist,
  lyrics: lyricsState,
};

type action =
  | Artist(Artist.artist)
  | Generate
  | Loading
  | Generated(string);

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _children => {
  ...component,

  initialState: () => {artist: Abba, lyrics: Idle},

  reducer: (action, state) =>
    switch (action) {
    | Artist(a) => ReasonReact.Update({...state, artist: a})
    | Generate =>
      ReasonReact.SideEffects(
        self => {
          self.send(Loading);
          Js.Promise.(
            Api.get_lyrics(self.state.artist)
            |> then_(res => {
                 self.send(Generated(res##data##data));
                 resolve();
               })
            |> ignore
          );
        },
      )
    | Generated(l) => ReasonReact.Update({...state, lyrics: Lyrics(l)})
    | Loading => ReasonReact.Update({...state, lyrics: Loading})
    },

  render: self => {
    <div className=Styles.wrap>
      <div className=Styles.artist_holder>
        {ReasonReact.array(
           Array.of_list(
             Artist.get_all()
             |> List.map(a =>
                  <Avatar
                    artist=a
                    onClick={_event => self.send(Artist(a))}
                    selected={
                      self.state.artist === a ? `Selected : `Not_selected
                    }
                  />
                ),
           ),
         )}
      </div>
      <button onClick={_event => self.send(Generate)}>
        {ReasonReact.string("Generate")}
      </button>
      {switch (self.state.lyrics) {
       | Loading => ReasonReact.string("Loading...")
       | Lyrics(lyrics) => <Card lyrics />
       | _ => ReasonReact.string("")
       }}
    </div>;
  },
};