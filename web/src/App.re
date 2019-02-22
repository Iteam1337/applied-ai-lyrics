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
      {switch (self.state.artist) {
       | Some(a) => <Lyrics artist=a />
       | None => "" |> ReasonReact.string
       }}
      <div className=Styles.artist_holder>
        {ReasonReact.array(
           Array.of_list(
             Artist.get_all()
             |> List.map(a =>
                  <Avatar
                    key={Artist.get_name(a)}
                    artist=a
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