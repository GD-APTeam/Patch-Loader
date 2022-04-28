# Patch-Loader

A dynamic Geometry Dash patch loader which makes use of a JSON patch configuration file.

## Structure

To configure the patch loader, create a JSON file called `patches.json` in the root directory of the game with the following structure:

```jsonc
[
  {
    "address": uint32_t, // The start memory address location of the patch
    "bytes": uint8_t[], // The bytes to write to the memory address
    "cocos": bool|undefined // If the patch should be applied to cocos2d.dll
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

- [HJfod](https://github.com/HJfod): Fact checking the bindings
- [Matcool](https://github.com/matcool): Providing the base minhook implementation example
