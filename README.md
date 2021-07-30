# TranslationVerification

[![GitHub (pre-)release](https://img.shields.io/github/release/pennyfea/TranslationVerification/all.svg)](https://github.com/pennyfea/TranslationVerification/releases/tag/v1.0.0)
[![CI/CD](https://github.com/pennyfea/TranslationVerification/actions/workflows/build.yml/badge.svg?branch=main)](https://github.com/pennyfea/TranslationVerification/actions/workflows/build.yml)

 **Translation Verification** is a simple translator and text length verifier written in C++ / Qt that allows you to translate text using Google's translate API. It leverages the [QOnlineTranslator](https://github.com/crow-translate/QOnlineTranslator) library for Qt5 that provides free usage of Google, Yandex and Bing translate API.
 
## Screenshots

![Translation-Verification](https://user-images.githubusercontent.com/22165430/133140778-cf9747e0-7326-445d-9daa-ead9612352fd.png)
 
## Features

- Translate text from screen or selection
- Determines if the text entered fits inside the specified text container width.
- Support 125 different languages
- Available for Linux and Windows
- Google translate API

## Dependencies

### Required

- [CMake](https://cmake.org) 3.11+
- [Qt](https://www.qt.io) 5.15.2

### External libraries

This project uses the following external library, which will be downloaded automatically at configure time using the built-in CMake [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html) module:

- [QOnlineTranslator](https://github.com/crow-translate/QOnlineTranslator) - provides free usage of Google, Yandex and Bing translate API.

## Installation

Downloads are available on the [Releases](https://github.com/pennyfea/TranslationVerification/releases/tag/v1.0.0) page

## Building

### Building a package using CPack

```bash
mkdir build
cd build
cmake .. # Or `cmake -DCMAKE_PREFIX_PATH=/path/to/Qt/5.15.2/{compiler} ..`
cpack
```

