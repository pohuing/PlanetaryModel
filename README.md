# Computergrafik Prüfungsleistung

Technologien:
- OpenGL4+ mit GLFW GLEW und GLM
- C++ 14
- Build mit premake5 auf Linux, Windows


Ziele:
- [x] Stark vereinfachtes Modell des Sonnensystem, Planeten bewegen sich auf kreisförmigen Bahnen um eine Sonne
- [x] Von der Sonne abgewandte Seiten sollen dunkel sein
- [x] Planeten sollen eine Textur haben
- [ ] Planeten sollen auf einander Schatten werfen können
- [x] Frei bewegliche Kamera

Installationsbeschreibung:
vs201x Solution mit jeweiligen mitgelieferten Skripten generieren
Solution mit Visual Studio öffnen und Debug oder Releasebuild ausühren
Exe, Modelle und Shader finden sich dann in bin/Release-xxx.

Windows Abhängigkeiten befinden sich unter THIRDPARTY, unter Linux sind die Pakete für GLFW und OpenGL Entwicklung erforderlich.

Texturen sind von http://planetpixelemporium.com/index.php genommen. 
Als Grundlage gilt das Khronos wiki: https://www.khronos.org/opengl/wiki/ 
Und die Anleitungen unter learnopengl.com