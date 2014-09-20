import("Lp3", "Lp3Project", "DEV")
require "Lp3Project"

Lp3Project{
  group="Lp3",
  project="Lp3.Math",
  version="DEV",
  src="src",
  target="target",
  libShortName="Lp3Math",
  dependencies = {
    load("Lp3", "Lp3.Engine.Core", "DEV"):Target("lib"),
  },
};

