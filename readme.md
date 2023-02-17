# このエンジンを使用する前に
* ExLibraryを既定の位置に配置してください。手順については[ExLibraryについて](#exlibraryについて)を参照してください。
* Visual Studio から起動する場合は、[Visual_Studioの設定について](#visual-studioの設定について)を参照してください。

# ExLibraryについて
(例)※バージョンによってファイル名やフォルダ名が違うかもしれません。
```
+---YonemaEngine
|	+---ExLibrary
|	|	+---DirectXTex-main
|	|	+---DirectXTK12-sept2021
|	|	+---PhysX-4.1
|	+---Game
|	+---Tools
|	.gitignore
```
上記の例のような階層構造になるようにExLibraryを配置してください。
ExLibraryは "Tools/ExLibrary ショートカット" からダウンロードして、zipを解凍してから配置してください。

ExLibraryを入手出来たら、dllを指定の位置にコピーする必要があります。
* ExLibrary\PhysX-4.1\PhysX-4.1\physx\bin\win.x86_64.vc142.md\debug
* ExLibrary\PhysX-4.1\PhysX-4.1\physx\bin\win.x86_64.vc142.md\Release

この二つのフォルダの中でそれぞれ、dllを検索して全てをコピーしてください。
ペーストする場所はdebugとreleaseのそれぞれのexeがある場所です。
デフォルトでは
* Game\x64\Debug
* Game\x64\Release

この二つのフォルダにあるはずですので、ここにペーストしてください。



# Visual Studioの設定について
1. Visual Studioのツールバーのプロジェクトを開いてください。
2. プロジェクト->Gameのプロパティを開いてください。
3. プロパティページが出てきたら、構成をReleaseにしてください。
4. 構成プロパティのデバッグのコマンドライン引数に何でもいいから文字列を入れてください。(念のためアルファベッド)