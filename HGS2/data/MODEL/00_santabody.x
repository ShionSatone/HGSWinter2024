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
 176;
 -0.30100;22.98667;-8.58107;,
 3.31822;22.98667;-8.10570;,
 3.31822;0.68667;-8.10570;,
 -0.30100;0.68667;-8.58107;,
 6.54524;22.98667;-6.73113;,
 6.54524;0.68667;-6.73113;,
 9.03037;22.98667;-4.60631;,
 9.03037;0.68667;-4.60631;,
 10.50430;22.98667;-1.96149;,
 10.50430;0.68667;-1.96149;,
 10.80730;22.98667;0.91671;,
 10.80730;0.68667;0.91671;,
 9.90655;22.98667;3.71641;,
 9.90655;0.68667;3.71641;,
 7.89965;22.98667;6.13421;,
 7.89965;0.68667;6.13421;,
 5.00409;22.98667;7.90810;,
 5.00409;0.68667;7.90810;,
 1.53363;22.98667;8.84586;,
 1.53363;0.68667;8.84586;,
 -2.13563;22.98667;8.84586;,
 -2.13563;0.68667;8.84586;,
 -5.60608;22.98667;7.90810;,
 -5.60608;0.68667;7.90810;,
 -8.50165;22.98667;6.13421;,
 -8.50165;0.68667;6.13421;,
 -10.50855;22.98667;3.71641;,
 -10.50855;0.68667;3.71641;,
 -11.40930;22.98667;0.91671;,
 -11.40930;0.68667;0.91671;,
 -11.10630;22.98667;-1.96150;,
 -11.10630;0.68667;-1.96150;,
 -9.63236;22.98667;-4.60632;,
 -9.63236;0.68667;-4.60632;,
 -7.14723;22.98667;-6.73114;,
 -7.14723;0.68667;-6.73114;,
 -3.92021;22.98667;-8.10571;,
 -3.92021;0.68667;-8.10571;,
 -0.30100;22.98667;-8.58107;,
 -0.30100;0.68667;-8.58107;,
 -0.30100;22.98667;0.19222;,
 -0.30100;22.98667;0.19222;,
 -0.30100;22.98667;0.19222;,
 -0.30100;22.98667;0.19222;,
 -0.30100;22.98667;0.19222;,
 -0.30100;22.98667;0.19222;,
 -0.30100;22.98667;0.19222;,
 -0.30100;22.98667;0.19222;,
 -0.30100;22.98667;0.19222;,
 -0.30100;22.98667;0.19222;,
 -0.30100;22.98667;0.19222;,
 -0.30100;22.98667;0.19222;,
 -0.30100;22.98667;0.19222;,
 -0.30100;22.98667;0.19222;,
 -0.30100;22.98667;0.19222;,
 -0.30100;22.98667;0.19222;,
 -0.30100;22.98667;0.19222;,
 -0.30100;22.98667;0.19222;,
 -0.30100;22.98667;0.19222;,
 -0.30100;0.68667;0.19222;,
 -0.30100;0.68667;0.19222;,
 -0.30100;0.68667;0.19222;,
 -0.30100;0.68667;0.19222;,
 -0.30100;0.68667;0.19222;,
 -0.30100;0.68667;0.19222;,
 -0.30100;0.68667;0.19222;,
 -0.30100;0.68667;0.19222;,
 -0.30100;0.68667;0.19222;,
 -0.30100;0.68667;0.19222;,
 -0.30100;0.68667;0.19222;,
 -0.30100;0.68667;0.19222;,
 -0.30100;0.68667;0.19222;,
 -0.30100;0.68667;0.19222;,
 -0.30100;0.68667;0.19222;,
 -0.30100;0.68667;0.19222;,
 -0.30100;0.68667;0.19222;,
 -0.30100;0.68667;0.19222;,
 -0.30100;0.68667;0.19222;,
 -0.30100;8.38044;-9.53886;,
 3.57996;8.38044;-9.02400;,
 3.57996;6.50140;-9.02400;,
 -0.30100;6.50140;-9.53886;,
 7.04037;8.38044;-7.53525;,
 7.04037;6.50140;-7.53525;,
 9.70521;8.38044;-5.23392;,
 9.70521;6.50140;-5.23392;,
 11.28573;8.38044;-2.36939;,
 11.28573;6.50140;-2.36939;,
 11.61064;8.38044;0.74791;,
 11.61064;6.50140;0.74791;,
 10.64476;8.38044;3.78018;,
 10.64476;6.50140;3.78018;,
 8.49273;8.38044;6.39883;,
 8.49273;6.50140;6.39883;,
 5.38775;8.38044;8.32007;,
 5.38775;6.50140;8.32007;,
 1.66631;8.38044;9.33573;,
 1.66631;6.50140;9.33573;,
 -2.26831;8.38044;9.33573;,
 -2.26831;6.50140;9.33573;,
 -5.98975;8.38044;8.32007;,
 -5.98975;6.50140;8.32007;,
 -9.09473;8.38044;6.39883;,
 -9.09473;6.50140;6.39883;,
 -11.24675;8.38044;3.78018;,
 -11.24675;6.50140;3.78018;,
 -12.21264;8.38044;0.74791;,
 -12.21264;6.50140;0.74791;,
 -11.88774;8.38044;-2.36940;,
 -11.88774;6.50140;-2.36940;,
 -10.30721;8.38044;-5.23393;,
 -10.30721;6.50140;-5.23393;,
 -7.64235;8.38044;-7.53526;,
 -7.64235;6.50140;-7.53526;,
 -4.18194;8.38044;-9.02401;,
 -4.18194;6.50140;-9.02401;,
 -0.30100;8.38044;-9.53886;,
 -0.30100;6.50140;-9.53886;,
 -0.30100;8.38044;-0.03677;,
 -0.30100;8.38044;-0.03677;,
 -0.30100;8.38044;-0.03677;,
 -0.30100;8.38044;-0.03677;,
 -0.30100;8.38044;-0.03677;,
 -0.30100;8.38044;-0.03677;,
 -0.30100;8.38044;-0.03677;,
 -0.30100;8.38044;-0.03677;,
 -0.30100;8.38044;-0.03677;,
 -0.30100;8.38044;-0.03677;,
 -0.30100;8.38044;-0.03677;,
 -0.30100;8.38044;-0.03677;,
 -0.30100;8.38044;-0.03677;,
 -0.30100;8.38044;-0.03677;,
 -0.30100;8.38044;-0.03677;,
 -0.30100;8.38044;-0.03677;,
 -0.30100;8.38044;-0.03677;,
 -0.30100;8.38044;-0.03677;,
 -0.30100;8.38044;-0.03677;,
 -0.30100;6.50140;-0.03677;,
 -0.30100;6.50140;-0.03677;,
 -0.30100;6.50140;-0.03677;,
 -0.30100;6.50140;-0.03677;,
 -0.30100;6.50140;-0.03677;,
 -0.30100;6.50140;-0.03677;,
 -0.30100;6.50140;-0.03677;,
 -0.30100;6.50140;-0.03677;,
 -0.30100;6.50140;-0.03677;,
 -0.30100;6.50140;-0.03677;,
 -0.30100;6.50140;-0.03677;,
 -0.30100;6.50140;-0.03677;,
 -0.30100;6.50140;-0.03677;,
 -0.30100;6.50140;-0.03677;,
 -0.30100;6.50140;-0.03677;,
 -0.30100;6.50140;-0.03677;,
 -0.30100;6.50140;-0.03677;,
 -0.30100;6.50140;-0.03677;,
 -0.30100;6.50140;-0.03677;,
 -1.78266;8.57859;-9.60227;,
 1.50521;8.57859;-9.60227;,
 1.50521;6.23639;-9.60227;,
 -1.78266;6.23639;-9.60227;,
 1.50521;8.57859;-9.60227;,
 1.50521;8.57859;-8.43132;,
 1.50521;6.23639;-8.43132;,
 1.50521;6.23639;-9.60227;,
 1.50521;8.57859;-8.43132;,
 -1.78266;8.57859;-8.43132;,
 -1.78266;6.23639;-8.43132;,
 1.50521;6.23639;-8.43132;,
 -1.78266;8.57859;-8.43132;,
 -1.78266;8.57859;-9.60227;,
 -1.78266;6.23639;-9.60227;,
 -1.78266;6.23639;-8.43132;,
 1.50521;8.57859;-9.60227;,
 -1.78266;8.57859;-9.60227;,
 -1.78266;6.23639;-9.60227;,
 1.50521;6.23639;-9.60227;;
 
 120;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 3;40,1,0;,
 3;41,4,1;,
 3;42,6,4;,
 3;43,8,6;,
 3;44,10,8;,
 3;45,12,10;,
 3;46,14,12;,
 3;47,16,14;,
 3;48,18,16;,
 3;49,20,18;,
 3;50,22,20;,
 3;51,24,22;,
 3;52,26,24;,
 3;53,28,26;,
 3;54,30,28;,
 3;55,32,30;,
 3;56,34,32;,
 3;57,36,34;,
 3;58,38,36;,
 3;59,3,2;,
 3;60,2,5;,
 3;61,5,7;,
 3;62,7,9;,
 3;63,9,11;,
 3;64,11,13;,
 3;65,13,15;,
 3;66,15,17;,
 3;67,17,19;,
 3;68,19,21;,
 3;69,21,23;,
 3;70,23,25;,
 3;71,25,27;,
 3;72,27,29;,
 3;73,29,31;,
 3;74,31,33;,
 3;75,33,35;,
 3;76,35,37;,
 3;77,37,39;,
 4;78,79,80,81;,
 4;79,82,83,80;,
 4;82,84,85,83;,
 4;84,86,87,85;,
 4;86,88,89,87;,
 4;88,90,91,89;,
 4;90,92,93,91;,
 4;92,94,95,93;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;98,100,101,99;,
 4;100,102,103,101;,
 4;102,104,105,103;,
 4;104,106,107,105;,
 4;106,108,109,107;,
 4;108,110,111,109;,
 4;110,112,113,111;,
 4;112,114,115,113;,
 4;114,116,117,115;,
 3;118,79,78;,
 3;119,82,79;,
 3;120,84,82;,
 3;121,86,84;,
 3;122,88,86;,
 3;123,90,88;,
 3;124,92,90;,
 3;125,94,92;,
 3;126,96,94;,
 3;127,98,96;,
 3;128,100,98;,
 3;129,102,100;,
 3;130,104,102;,
 3;131,106,104;,
 3;132,108,106;,
 3;133,110,108;,
 3;134,112,110;,
 3;135,114,112;,
 3;136,116,114;,
 3;137,81,80;,
 3;138,80,83;,
 3;139,83,85;,
 3;140,85,87;,
 3;141,87,89;,
 3;142,89,91;,
 3;143,91,93;,
 3;144,93,95;,
 3;145,95,97;,
 3;146,97,99;,
 3;147,99,101;,
 3;148,101,103;,
 3;149,103,105;,
 3;150,105,107;,
 3;151,107,109;,
 3;152,109,111;,
 3;153,111,113;,
 3;154,113,115;,
 3;155,115,117;,
 4;156,157,158,159;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;168,161,172,173;,
 4;174,175,162,171;;
 
 MeshMaterialList {
  3;
  120;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.000000;0.009412;1.000000;;
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
   0.800000;0.743529;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  48;
  0.000000;1.000000;0.000000;,
  0.000001;0.000000;-1.000000;,
  0.263490;0.000000;-0.964662;,
  0.526977;0.000000;-0.849880;,
  0.773843;0.000000;-0.633378;,
  0.953349;0.000000;-0.301872;,
  0.994680;0.000000;0.103009;,
  0.876605;0.000000;0.481210;,
  0.654728;0.000000;0.755864;,
  0.395653;0.000000;0.918400;,
  0.131572;0.000000;0.991307;,
  -0.131572;0.000000;0.991307;,
  -0.395653;0.000000;0.918400;,
  -0.654728;0.000000;0.755865;,
  -0.876605;0.000000;0.481210;,
  -0.994681;0.000000;0.103008;,
  -0.953348;0.000000;-0.301872;,
  -0.773842;0.000000;-0.633378;,
  -0.526976;0.000000;-0.849880;,
  -0.263489;0.000000;-0.964662;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.265854;0.000000;-0.964013;,
  0.530601;0.000000;-0.847622;,
  0.776737;0.000000;-0.629825;,
  0.954140;0.000000;-0.299361;,
  0.994776;0.000000;0.102082;,
  0.878474;0.000000;0.477790;,
  0.658256;0.000000;0.752794;,
  0.398855;0.000000;0.917014;,
  0.132823;0.000000;0.991140;,
  -0.132823;0.000000;0.991140;,
  -0.398854;0.000000;0.917014;,
  -0.658257;0.000000;0.752794;,
  -0.878475;0.000000;0.477789;,
  -0.994776;0.000000;0.102084;,
  -0.954140;0.000000;-0.299360;,
  -0.776735;0.000000;-0.629827;,
  -0.530599;0.000000;-0.847623;,
  -0.265854;0.000000;-0.964013;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  120;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,19,19,18;,
  4;19,1,1,19;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  4;22,23,23,22;,
  4;23,24,24,23;,
  4;24,25,25,24;,
  4;25,26,26,25;,
  4;26,27,27,26;,
  4;27,28,28,27;,
  4;28,29,29,28;,
  4;29,30,30,29;,
  4;30,31,31,30;,
  4;31,32,32,31;,
  4;32,33,33,32;,
  4;33,34,34,33;,
  4;34,35,35,34;,
  4;35,36,36,35;,
  4;36,37,37,36;,
  4;37,38,38,37;,
  4;38,39,39,38;,
  4;39,40,40,39;,
  4;40,22,22,40;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;47,47,47,47;;
 }
 MeshTextureCoords {
  176;
  0.000000;0.000000;,
  0.052632;0.000000;,
  0.052632;1.000000;,
  0.000000;1.000000;,
  0.105263;0.000000;,
  0.105263;1.000000;,
  0.157895;0.000000;,
  0.157895;1.000000;,
  0.210526;0.000000;,
  0.210526;1.000000;,
  0.263158;0.000000;,
  0.263158;1.000000;,
  0.315789;0.000000;,
  0.315789;1.000000;,
  0.368421;0.000000;,
  0.368421;1.000000;,
  0.421053;0.000000;,
  0.421053;1.000000;,
  0.473684;0.000000;,
  0.473684;1.000000;,
  0.526316;0.000000;,
  0.526316;1.000000;,
  0.578947;0.000000;,
  0.578947;1.000000;,
  0.631579;0.000000;,
  0.631579;1.000000;,
  0.684210;0.000000;,
  0.684210;1.000000;,
  0.736842;0.000000;,
  0.736842;1.000000;,
  0.789474;0.000000;,
  0.789474;1.000000;,
  0.842105;0.000000;,
  0.842105;1.000000;,
  0.894737;0.000000;,
  0.894737;1.000000;,
  0.947368;0.000000;,
  0.947368;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.026316;0.000000;,
  0.078947;0.000000;,
  0.131579;0.000000;,
  0.184211;0.000000;,
  0.236842;0.000000;,
  0.289474;0.000000;,
  0.342105;0.000000;,
  0.394737;0.000000;,
  0.447368;0.000000;,
  0.500000;0.000000;,
  0.552632;0.000000;,
  0.605263;0.000000;,
  0.657895;0.000000;,
  0.710526;0.000000;,
  0.763158;0.000000;,
  0.815789;0.000000;,
  0.868421;0.000000;,
  0.921053;0.000000;,
  0.973684;0.000000;,
  0.026316;1.000000;,
  0.078947;1.000000;,
  0.131579;1.000000;,
  0.184211;1.000000;,
  0.236842;1.000000;,
  0.289474;1.000000;,
  0.342105;1.000000;,
  0.394737;1.000000;,
  0.447368;1.000000;,
  0.500000;1.000000;,
  0.552632;1.000000;,
  0.605263;1.000000;,
  0.657895;1.000000;,
  0.710526;1.000000;,
  0.763158;1.000000;,
  0.815789;1.000000;,
  0.868421;1.000000;,
  0.921053;1.000000;,
  0.973684;1.000000;,
  0.000000;0.000000;,
  0.052632;0.000000;,
  0.052632;1.000000;,
  0.000000;1.000000;,
  0.105263;0.000000;,
  0.105263;1.000000;,
  0.157895;0.000000;,
  0.157895;1.000000;,
  0.210526;0.000000;,
  0.210526;1.000000;,
  0.263158;0.000000;,
  0.263158;1.000000;,
  0.315789;0.000000;,
  0.315789;1.000000;,
  0.368421;0.000000;,
  0.368421;1.000000;,
  0.421053;0.000000;,
  0.421053;1.000000;,
  0.473684;0.000000;,
  0.473684;1.000000;,
  0.526316;0.000000;,
  0.526316;1.000000;,
  0.578947;0.000000;,
  0.578947;1.000000;,
  0.631579;0.000000;,
  0.631579;1.000000;,
  0.684210;0.000000;,
  0.684210;1.000000;,
  0.736842;0.000000;,
  0.736842;1.000000;,
  0.789474;0.000000;,
  0.789474;1.000000;,
  0.842105;0.000000;,
  0.842105;1.000000;,
  0.894737;0.000000;,
  0.894737;1.000000;,
  0.947368;0.000000;,
  0.947368;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.026316;0.000000;,
  0.078947;0.000000;,
  0.131579;0.000000;,
  0.184211;0.000000;,
  0.236842;0.000000;,
  0.289474;0.000000;,
  0.342105;0.000000;,
  0.394737;0.000000;,
  0.447368;0.000000;,
  0.500000;0.000000;,
  0.552632;0.000000;,
  0.605263;0.000000;,
  0.657895;0.000000;,
  0.710526;0.000000;,
  0.763158;0.000000;,
  0.815789;0.000000;,
  0.868421;0.000000;,
  0.921053;0.000000;,
  0.973684;0.000000;,
  0.026316;1.000000;,
  0.078947;1.000000;,
  0.131579;1.000000;,
  0.184211;1.000000;,
  0.236842;1.000000;,
  0.289474;1.000000;,
  0.342105;1.000000;,
  0.394737;1.000000;,
  0.447368;1.000000;,
  0.500000;1.000000;,
  0.552632;1.000000;,
  0.605263;1.000000;,
  0.657895;1.000000;,
  0.710526;1.000000;,
  0.763158;1.000000;,
  0.815789;1.000000;,
  0.868421;1.000000;,
  0.921053;1.000000;,
  0.973684;1.000000;,
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
