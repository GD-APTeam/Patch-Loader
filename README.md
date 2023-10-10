# Patch-Loader

A dynamic Geometry Dash patch loader which makes use of a JSON patch configuration file.

## Structure

To configure the patch loader, create a JSON file called `patches.json` in the root directory of the game with the following structure:

```jsonc
[
  {
    "name": string, // The name which should be shown in the patch browser
    "description": string | null, // The description which should be shown in the patch browser
    "patches": [ // A list of patches which should be applied once enabled
      "label": string, // The label to identify the patch
      "address": uint32_t, // The memory address to write to
      "offsets": uint32_t[] | null, // The offsets to navigate through pointers to get to the memory address
      "cocos": bool | null, // If the patch should be applied to libcocos2d.dll
      // The following fields are mutually exclusive, one of them must be present
      "bytes": byte[] | null, // The bytes to write to the memory address
      "range": { // The info about a range patch which allows the user to select a number in a range
        "start": int, // The inclusive start of the range
        "end": int, // The inclusive end of the range
        "size": 1...4, // The amount of bytes the range is writing to
      } | null,
      "checkbox": bool | null, // If the patch is a checkbox which only writes 0 or 1 to the memory address
      "color" bool | null // If the patch is a color picker which writes a color to the memory address
    ],
    "restart": bool | null, // If the patch requires a restart
    "enabled": bool | null // If the patch should be enabled by default
  }
]
```

Any fields which are `null` will be ignored and can be omitted from the JSON.

## Installation

1. Install the latest release of [ProxyDllLoader](https://github.com/adafcaefc/ProxyDllLoader/releases/latest)
2. Put the latest release of [Patch-Loader](https://github.com/GD-APTeam/Patch-Loader/releases/latest) in the `adaf-dll` directory
3. Make a file called `patches.json` in the root directory of the game
4. Configure it using the structure [above](#structure)

## Building

Simply run the [shell file](compile.sh) to build the DLL.

## Credits

- [HJfod](https://github.com/HJfod): Fact checking the bindings and helping out a lot with the list view
