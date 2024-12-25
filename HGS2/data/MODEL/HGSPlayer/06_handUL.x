xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 40;
 -0.00229;2.92814;-3.61386;,
 -0.05296;-2.87645;-3.61386;,
 -4.57112;-2.83703;-3.61386;,
 -4.52047;2.96758;-3.61386;,
 -0.05296;-2.87645;-3.61386;,
 -0.05296;-2.87645;3.90624;,
 -4.57112;-2.83703;3.90624;,
 -4.57112;-2.83703;-3.61386;,
 -0.05296;-2.87645;3.90624;,
 -0.00229;2.92814;3.90624;,
 -4.52047;2.96758;3.90624;,
 -4.57112;-2.83703;3.90624;,
 -0.00229;2.92814;3.90624;,
 -0.00229;2.92814;-3.61386;,
 -4.52047;2.96758;-3.61386;,
 -4.52047;2.96758;3.90624;,
 -0.05296;-2.87645;-3.61386;,
 -0.00229;2.92814;-3.61386;,
 -4.52047;2.96758;-3.61386;,
 -4.57112;-2.83703;-3.61386;,
 -4.54148;2.96774;-3.11705;,
 -4.59213;-2.83684;-3.11705;,
 -9.70647;-2.79221;-3.11705;,
 -9.65580;3.01238;-3.11705;,
 -4.59213;-2.83684;-3.11705;,
 -4.59213;-2.83684;3.40943;,
 -9.70647;-2.79221;3.40943;,
 -9.70647;-2.79221;-3.11705;,
 -4.59213;-2.83684;3.40943;,
 -4.54148;2.96774;3.40943;,
 -9.65580;3.01238;3.40943;,
 -9.70647;-2.79221;3.40943;,
 -4.54148;2.96774;3.40943;,
 -4.54148;2.96774;-3.11705;,
 -9.65580;3.01238;-3.11705;,
 -9.65580;3.01238;3.40943;,
 -4.59213;-2.83684;-3.11705;,
 -4.54148;2.96774;-3.11705;,
 -9.65580;3.01238;-3.11705;,
 -9.70647;-2.79221;-3.11705;;
 
 12;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;;
 
 MeshMaterialList {
  6;
  12;
  4,
  4,
  4,
  4,
  4,
  4,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;0.749020;0.509804;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\awasetetukau_me14.png";
   }
  }
  Material {
   1.000000;0.396078;0.396078;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.211765;0.819608;0.949020;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.619608;0.376471;0.282353;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  10;
  0.000000;0.000000;-1.000000;,
  -0.008724;-0.999962;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.008727;-0.999962;0.000000;,
  0.008729;0.999962;0.000000;,
  0.999962;-0.008728;-0.000000;,
  -0.999962;0.008726;0.000000;,
  0.008727;0.999962;0.000000;,
  0.999962;-0.008726;-0.000000;,
  -0.999962;0.008728;0.000000;;
  12;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;;
 }
 MeshTextureCoords {
  40;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
