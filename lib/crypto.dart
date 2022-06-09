// ignore_for_file: non_constant_identifier_names

import 'dart:convert';
//import 'dart:math';
import 'package:http/http.dart' as http;

///Erstellt ein Link, welcher eine API eines Quantencomputers ansteuert.
///
/// Als Eingabe [length] wird eine Ganzzahl angenommen, die 1 >= [length] <= 1024 ist.
String Qrand(int length){
  assert(length <= 1024 && length >= 1);

  return "https://qrng.anu.edu.au/API/jsonI.php?length=$length&type=uint8";
}

///Generiert ein auf echtes Zufallszahlen basiertes Passwort.
///
/// Als Eingabe muss die Liste [verbotene_symbole] 5 bool'sche Werte beinhalten sowie die Passwortlänge [pwlen] als double.
Future<List> Gen_Password(List<bool> verbotene_symbole, double pwlen) async {
  //int entropy_R = 0;
  String versym = "";
  if(!verbotene_symbole[0]){
    versym = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //entropy_R += versym.length;
  }
  if(!verbotene_symbole[1]){
    versym += "abcdefghijklmnopqrstuvwxyz";
    //entropy_R += versym.length;
  }
  if(!verbotene_symbole[2]){
    versym += "0123456789";
    //entropy_R += versym.length;
  }
  if(!verbotene_symbole[3]){
    versym += """!\\"§\$%&/()=?*'<>;,:.-_+#~@{[]}´`|°^""";
    //entropy_R += versym.length;
  }
  if(!verbotene_symbole[4]){
    versym += "€‚ƒ„…†‡ˆ‰Š‹ŒŽ‘’“”•–—˜™š›œžŸ¡¢£¤¥¦§¨©ª«¬®¯±²³µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ";
    //entropy_R += versym.length;
  }

  var _symL = """
    ABCDEFGHIJKLMNOPQRSTUVWXYZ
    abcdefghijklmnopqrstuvwxyz
    0123456789
    !\\"§\$%&/()=?*'<>;,:.-_+#~@{[]}´`|°^
    €‚ƒ„…†‡ˆ‰Š‹ŒŽ‘’“”•–—˜™š›œžŸ¡¢£¤¥¦§¨©ª«¬®¯±²³µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ
    """.replaceAll("\n", "").replaceAll(" ", "").split("");
  /*if(versym == ""){
    entropy_R = _symL.length;
  }*/
  String _sym = _symL.join("");
  String _erlSym = _sym;
  for(int j = 0; j < versym.length; j++){
    _erlSym = _erlSym.replaceAll(versym.split("")[j], "");
  }

    while(_erlSym.length <= 255){
      _erlSym += _erlSym.split("").join("").toString();
    }
  var _qrand = (await http.get(Uri.parse(Qrand(pwlen.toInt()>255?pwlen.toInt():255)))).body;
  final Map _qrandD = json.decode(_qrand);
  var _numbers = _qrandD["data"];

  String _pwd = "";
  if(pwlen.toInt() > _erlSym.length){
    _erlSym *= pwlen.toInt() ~/ 255;
  }
  for(var _num in _numbers){
    _pwd = "$_pwd${_erlSym.split("")[_num]}";
  }
  //var entropy = log(entropy_R) * pwlen;
  return [_pwd.substring(0, pwlen.toInt())];
}