let component = ReasonReact.statelessComponent(__MODULE__);

let make = (~artist, ~lyrics, _children) => {
  ...component,

  render: _self => {
    let artist_name = artist |> Artist.get_name;

    <div className=Styles.lyrics_holder>
      <div className=Styles.lyrics_text>
        {lyrics |> ReasonReact.string}
        <span className=Styles.lyrics_artist>
          {{j|– $artist_name ITEAM |j} |> ReasonReact.string}
        </span>
      </div>
    </div>;
  },
};