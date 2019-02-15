let component = ReasonReact.statelessComponent(__MODULE__);

let make = (~lyrics, _children) => {
  ...component,

  render: _self => {
    <div className=Styles.lyrics_holder> {lyrics |> ReasonReact.string} </div>;
  },
};