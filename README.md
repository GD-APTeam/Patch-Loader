# Patch-Loader

A dynamic Geometry Dash patch loader which makes use of a JSON patch configuration file.

## Structure

To configure the patch loader, create a JSON file called `patches.json` in the root directory of the game with the following structure:

```jsonc
[
  {
    "name": string, // The name which should be shown in the patch browser
    "description": string|undefined|null, // The description which should be shown in the patch browser
    "address": uint32_t, // The start memory address location of the patch
    "bytes": byte[], // The bytes to write to the memory address
    "cocos": bool|undefined|null, // If the patch should be applied to cocos2d.dll
    "disabled": bool|undefined|null, // If the patch should be ignored
    "restart": bool|undefined|null, // If the patch requires a restart
    // A patch collection, this will group multiple patches together
    // Keep in mind that patches within cannot be toggled individually in-game
    // However they can be toggled in the configuration file
    // address, bytes, cocos and restart will be ignored if patches is set
    "patches": this|undefined|null
  }
]
```

## Installation

1. Install the latest release of [ProxyDllLoader](https://github.com/adafcaefc/ProxyDllLoader/releases/latest)
2. Put the latest release of [Patch-Loader](https://github.com/SMJSGaming/Patch-Loader/releases/latest) in the `adaf-dll` directory
3. Make a file called `patches.json` in the root directory of the game
4. Configure it using the structure [above](#structure)

## Building

Simply run the [shell file](compile.sh) to build the DLL.

## Credits

- [HJfod](https://github.com/HJfod): Fact checking the bindings and helping out a lot with the list view
- [Matcool](https://github.com/matcool): Providing the base minhook/gd.h implementation example
