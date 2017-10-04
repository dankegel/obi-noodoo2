# {{project_name}}
An amazing g-speak project.


# The project.yaml file

[project.yaml](project.yaml) contains all the information for building and running your g-speak application, if you use `obi` as your project runner tool.  It lets you specify launch options such as command arguments, environment vars, etc.

When running on your own machine (`obi go`), obi uses information from the `localhost` room in [project.yaml](project.yaml).


## Run locally
```bash
obi go
```

## Build locally
```bash
obi build
```

## Run in a room enviornment
```bash
obi go <room-name>
```

Where `<room-name>` is the name of one of the keys specified in the `rooms` map in [project.yaml](project.yaml).

## Stop the app

	obi stop [<room-name>]


## Sublime Text Users

This project has a [sublime-project file]({{project_name}}.sublime-project) that comes equipped with some useful build systems:

- `obi-build`: just build the app
- `obi-go`: build and run the app
- `obi-go:my-room`: build and run the app in your custom room *NOTE:* Requires custom setup in your project.yaml


## Riding without obi

### Build
```bash
cd build
cmake -DG_SPEAK_HOME=/opt/oblong/g-speak{{g_speak_version}} ..
make -j8 -l8
```

### Run
```bash
build/{{project_name}} [(<screen.protein> <feld.protein>)]
```

### Change default g-speak version
obi detects the g-speak version present at the time, and sets that
as the project's default.  To switch g-speak or cef versions, you can
change the default by running ob-set-defaults (included with the g-speak
platform SDK).  For instance,
```bash
ob-set-defaults --g-speak 4.2
```
Try 'ob-set-defaults --help' for more info.

### Build packages (mostly Oblong-specific)
The tool bau, included with the g-speak platform SDK,
is a bit like obi, but centers around building packages
for production rather than creating and running projects.

It can build linux and mac packages given the settings in ci/* and debian/*,
and the default recipes in /usr/bin/bau-defaults.

For instance,
```bash
bau all
```
It takes the same options as ob-set-defaults.  Try 'bau --help' and 'bau help' for more info.

