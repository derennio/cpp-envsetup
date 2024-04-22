# EnvSetup
## Anwendung mit den mitgeliederten Beispieldateien
### Ins Build-Verzeichnis wechseln
``` cd build ```

### Programm bauen
``` cmake .. && make ```

### Beispieldateien aufrufen: Eine wird von GitHub bezogen, die andere aus dem sample-Verzeichnis
``` ./EnvSetup https://raw.githubusercontent.com/derennio/cpp-envsetup/main/sample/MinGW.json ../sample/VSCodeMinGW.json ```

## Hinweise zur Erfüllerung der Anforderungen
1. Header-Dateien sind im include-Verzeichnis abgelegt und via CMake eingebunden. Externe Bibliotheken sind im external-Verzeichnis abgelegt, bzw. Library-Object-Files im lib-Verzeichnis hinterlegt.
2. cURL wird als Standardkommand auf Windows verwendet, um Dateien aus dem Netz herunterzuladen, ohne weitere Library-Object-Files im Code einzubinden, welche eventuell plattformabhängig sein können.

