import 'package:flutter/material.dart';
import 'crypto.dart' as crypto;
import 'firebase.dart' as firebase;
import 'package:firebase_core/firebase_core.dart';
import 'package:get/get.dart';
import 'package:http/http.dart' as http;
import 'package:cloud_firestore/cloud_firestore.dart';

List _pwd = [];
bool _UC = true;
bool _LC = true;
bool _num = true;
bool _sym = true;
bool _erwASCII = false;
bool _offlinemode = false;
double _pwlen = 8;
String _note = "";


/*
* Theme Farben
* */
List<Color> colors = const [
  // Dunkel
  Color(0xff800080), //0
  Color(0xff8c008c), //1
  Color(0xffCC00CC), //2
  // Hell
  Color(0xff00CC00), //3
  Color(0xff00A600), //4
  Color(0xff008000)  //5
];

Future<void> main() async {
  runApp(
    GetMaterialApp(
      debugShowCheckedModeBanner: false,

      /*
      * Light Theme Einstellungen
      * */
      theme: ThemeData.light().copyWith(
        buttonTheme: ButtonThemeData(
          buttonColor: colors[4],
          textTheme: ButtonTextTheme.primary,
        ),
        textButtonTheme: TextButtonThemeData(
          style: TextButton.styleFrom(
              primary: colors[5]
          ),
        ),
        elevatedButtonTheme: ElevatedButtonThemeData(
            style: ElevatedButton.styleFrom(
                primary: colors[4]
            )
        ),
        sliderTheme: SliderThemeData(
            thumbColor: colors[4],
            activeTrackColor: colors[5],
            inactiveTrackColor: colors[3]
        ),
        switchTheme: const SwitchThemeData().copyWith(
            thumbColor: MaterialStateProperty.all(colors[4]),
            trackColor: MaterialStateProperty.all(colors[3])
        ),
        appBarTheme: AppBarTheme(
          color: colors[3],
        ),
        inputDecorationTheme: const InputDecorationTheme().copyWith(
            enabledBorder: const OutlineInputBorder().copyWith(
              borderSide: const BorderSide().copyWith(
                  color: colors[4]
              ),
              borderRadius: BorderRadius.circular(50.0),
            ),
            focusedBorder: const OutlineInputBorder().copyWith(
              borderSide: const BorderSide().copyWith(
                  color: colors[5]
              ),
              borderRadius: BorderRadius.circular(50.0),
            )
        )
      ),

      /*
      * Dark Theme Einstellung
      * */
      darkTheme: ThemeData.dark().copyWith(
        buttonTheme: ButtonThemeData(
          buttonColor: colors[1],
          textTheme: ButtonTextTheme.primary,
        ),
        textButtonTheme: TextButtonThemeData(
          style: TextButton.styleFrom(
              primary: colors[2]
          ),
        ),
        elevatedButtonTheme: ElevatedButtonThemeData(
          style: ElevatedButton.styleFrom(
            primary: colors[1]
          )
        ),
        sliderTheme: SliderThemeData(
          thumbColor: colors[1],
          activeTrackColor: colors[2],
          inactiveTrackColor: colors[0]
        ),
        switchTheme: const SwitchThemeData().copyWith(
          thumbColor: MaterialStateProperty.all(colors[1]),
          trackColor: MaterialStateProperty.all(colors[0])
        ),
        appBarTheme: AppBarTheme(
          color: colors[0],
        ),
        inputDecorationTheme: const InputDecorationTheme().copyWith(
          enabledBorder: const OutlineInputBorder().copyWith(
            borderSide: const BorderSide().copyWith(
                color: colors[1]
            ),
            borderRadius: BorderRadius.circular(50.0),
          ),
          focusedBorder: const OutlineInputBorder().copyWith(
              borderSide: const BorderSide().copyWith(
                  color: colors[2]
              ),
              borderRadius: BorderRadius.circular(50.0),
          )
        )
      ),
      themeMode: ThemeMode.dark,
      title: "ProjektX Passwort Generator",
      initialRoute: '/',
      /*
      * Appübersicht
      * */
      routes: {
        '/': (context) => const firebase.LoginPage(),
        '/register': (context) => firebase.RegisterPage(),
        '/forgot': (context) => firebase.ForgotPassword(),
        '/second': (context) => const GeneratorEinstellungen(),
        '/settings': (context) => const Settings(),
        '/view': (context) => firebase.DatenbankView()
      },
    )
  );
  await Firebase.initializeApp();
}

/*****************************************************************
 *
 *                       Page 2
 *                   Random PW GEN
 *
 ******************************************************************/

class GeneratorEinstellungen extends StatefulWidget {
  const GeneratorEinstellungen({Key? key}) : super(key: key);

  @override
  _GeneratorEinstellungen createState() => _GeneratorEinstellungen();
}
class _GeneratorEinstellungen extends State<GeneratorEinstellungen>{
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: const Text(
            "Passwort Generator",
          ),
          actions: [
            Center(
              child: IconButton(
                icon: const Icon(Icons.table_chart),
                onPressed: (){
                  Navigator.pushNamed(context, '/view'); // DBN View
                },
              ),
            ),
            Center(
              child: IconButton(
                icon: const Icon(Icons.settings),
                onPressed: (){
                  Navigator.pushNamed(context, '/settings');
                },
              ),
            )
          ],
        ),
        body: SingleChildScrollView(
          child: Column(
            children: const [
              pwlenSlider(),
              pwOptions(),
              GenPwd()
            ],
          ),
        )
    );
  }
}

class pwlenSlider extends StatefulWidget{
  const pwlenSlider({Key? key}) : super(key: key);

  @override
  _pwlenSlider createState() => _pwlenSlider();
}

class _pwlenSlider extends State<pwlenSlider> {

  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        Row(
          children: [
            Text(
                "Länge: ${_pwlen.round()}",
            ),
            Slider(
              value: _pwlen,
              min: 8,
              max: 512,
              divisions: 512-8,
              label: _pwlen.toString(),
              onChanged: (double value){
                setState(() {
                  _pwlen = value;
                });
              },
            )
          ],
        ),

      ],
    );
  }
}

class pwOptions extends StatefulWidget{
  const pwOptions({Key? key}) : super(key: key);

  @override
  _pwOptions createState() => _pwOptions();
}

class _pwOptions extends State<pwOptions> {

  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        Row(
          children: [
            Row(
              children: [
                Switch(
                  value: _UC,
                  onChanged: (value) {
                    setState(() {
                      _UC = value;
                    });
                  },
                ),
                Tooltip(
                  message: 'Alle Großbuchstaben des Alphabets (ohne Umlaute).',
                  child: const Text(
                      "Großbuchstaben",
                  ),
                  decoration: BoxDecoration(
                    borderRadius: BorderRadius.circular(25),
                    gradient: const LinearGradient(colors: <Color>[Colors.blue, Colors.lightBlue]),
                  ),
                  height: 20,
                  padding: const EdgeInsets.all(8),
                  preferBelow: false,
                  textStyle: const TextStyle(
                    fontSize: 12,
                  ),
                  showDuration: const Duration(seconds: 2),
                  waitDuration: const Duration(seconds: 1),
                )
              ],
            ),
            Row(
              children: [
                Switch(
                  value: _num,
                  onChanged: (value) {
                    setState(() {
                      _num = value;
                    });
                  },
                ),
                Tooltip(
                  message: 'Zahlen von 0-9.',
                  child: const Text(
                      "Zahlen",
                  ),
                  decoration: BoxDecoration(
                    borderRadius: BorderRadius.circular(25),
                    gradient: const LinearGradient(colors: <Color>[Colors.blue, Colors.lightBlue]),
                  ),
                  height: 20,
                  padding: const EdgeInsets.all(8),
                  preferBelow: false,
                  textStyle: const TextStyle(
                    fontSize: 12,
                  ),
                  showDuration: const Duration(seconds: 2),
                  waitDuration: const Duration(seconds: 1),
                )
              ],
            )
          ],
        ),
        Row(
          children: [
            Row(
              children: [
                Switch(
                  value: _sym,
                  onChanged: (value) {
                    setState(() {
                      _sym = value;
                    });
                  },
                ),
                Tooltip(
                  message: """!\\"§\$%&/()=?*'<>;,:.-_+#~@{[]}´`|°^""",
                  child: const Text(
                      "Symbole",
                  ),
                  decoration: BoxDecoration(
                    borderRadius: BorderRadius.circular(25),
                    gradient: const LinearGradient(colors: <Color>[Colors.blue, Colors.lightBlue]),
                  ),
                  height: 20,
                  padding: const EdgeInsets.all(8),
                  preferBelow: false,
                  textStyle: const TextStyle(
                    fontSize: 12,
                  ),
                  showDuration: const Duration(seconds: 2),
                  waitDuration: const Duration(seconds: 1),
                )
              ],
            ),
            Row(
              children: [
                Switch(
                  value: _LC,
                  onChanged: (value) {
                    setState(() {
                      _LC = value;
                    });
                  },
                ),
                Tooltip(
                  message: 'Alle Kleinbuchstaben des Alphabets (ohne Umlaute).',
                  child: const Text(
                      "Kleinbuchstaben",
                  ),
                  decoration: BoxDecoration(
                    borderRadius: BorderRadius.circular(25),
                    gradient: const LinearGradient(colors: <Color>[Colors.blue, Colors.lightBlue]),
                  ),
                  height: 20,
                  padding: const EdgeInsets.all(8),
                  preferBelow: false,
                  textStyle: const TextStyle(
                    fontSize: 12,
                  ),
                  showDuration: const Duration(seconds: 2),
                  waitDuration: const Duration(seconds: 1),
                )
              ],
            ),
          ],
        ),
        Row(
          children: [
            Switch(
              value: _erwASCII,
              onChanged: (value) {
                setState(() {
                  _erwASCII = value;
                });
              },
            ),
            Tooltip(
              message: '€‚ƒ„…†‡ˆ‰Š‹ŒŽ‘’“”•–—\n˜™š›œžŸ¡¢£¤¥¦§¨©ª«¬®\n¯±²³µ¶·¸¹º»¼½¾¿ÀÁÂÃÄ\nÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×Ø\nÙÚÛÜÝÞßàáâãäåæçèéêëì\níîïðñòóôõö÷øùúûüýþÿ',
              child: const Text(
                  "Erw. ASCII",
              ),
              decoration: BoxDecoration(
                borderRadius: BorderRadius.circular(25),
                gradient: const LinearGradient(colors: <Color>[Colors.blue, Colors.lightBlue]),
              ),
              height: 20,
              padding: const EdgeInsets.all(8),
              preferBelow: false,
              textStyle: const TextStyle(
                fontSize: 12,
              ),
              showDuration: const Duration(seconds: 2),
              waitDuration: const Duration(seconds: 1),
            )
          ],
        )
      ],
    );
  }
}

class GenPwd extends StatefulWidget{
  const GenPwd({Key? key}) : super(key: key);

  @override
  _pwgen createState() => _pwgen();
}

class _pwgen extends State<GenPwd> {
  bool _isLoading = false;

  void _Loading() async {
    setState(() {
      _isLoading = !_isLoading;
    });
  }
  updatepwd(){
    pwd = _pwd[0];
  }
  String pwd = "";

  @override
  Widget build(BuildContext context) {
    return Column(
      children: [
        Row(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            _isLoading? const CircularProgressIndicator() : TextButton(
              onPressed: () async {
                if(_UC == _LC && _LC == _num && _num == _sym && _sym == _erwASCII && _erwASCII == false){
                  showDialog(
                      context: context,
                      builder: (ctx) => const AlertDialog(
                        title: Text("Achtung"),
                        content: Text('Mindestens eine Symbolgruppe muss gewählt werden!'),
                      )
                  );
                }else {
                  var error;
                  try{
                    var req = await http.get(Uri.parse("https://qrng.anu.edu.au"));
                    error = req.statusCode;
                  }catch (e){
                    error = int.parse(e.toString().split("=").last.split(")")[0].toString());
                  }
                  if(error == 200){
                    _Loading();
                    _pwd = await crypto.Gen_Password([_UC, _LC, _num, _sym, _erwASCII], _pwlen);
                    setState(() {
                      updatepwd();
                    });
                    _Loading();
                  }else{
                    showDialog(
                        context: context,
                        builder: (ctx) => const AlertDialog(
                          title: Text("Achtung"),
                          content: Text('Es konnte keine Internetverbindung hergestellt werden.'),
                        )
                    );
                  }
                }
              },
              child: const Text("Generiere Passwort"),
            ),
            TextButton(
              onPressed: (){
                showDialog(
                    context: context,
                    builder: (ctx) => AlertDialog(
                      title: const Text("Notiz"),
                      content: TextField(
                        decoration: const InputDecoration(
                          hintText: "Wofür ist das Passwort?"
                        ),
                        onChanged: (value) {
                          setState(() {
                              _note = value;
                          });
                        },
                      ),
                      actions: [
                        TextButton(onPressed: () {
                          FirebaseFirestore.instance.collection(firebase.createcollection()).add({
                            "notiz": null,
                            "passwort": _pwd,
                            "Erstellt am": DateTime.now()
                          });
                          Navigator.pop(context);
                        }, child: const Text("Abbruch")),
                        TextButton(onPressed: () {
                          FirebaseFirestore.instance.collection(firebase.createcollection()).add({
                            "notiz": _note,
                            "passwort": _pwd,
                            "Erstellt am": DateTime.now()
                          });
                          Navigator.pop(context);
                          ScaffoldMessenger.of(context).showSnackBar(
                            const SnackBar(
                              content: Text("Gespeichert."),
                              duration: Duration(seconds: 2),
                            )
                          );
                        }, child: const Text("Speichern")),
                      ],
                    )
                );
                setState(() {

                });
              },
              child: const Text("Speichern"),
            )
          ],
        ),
        SizedBox(
          width: 150,
          child: Column(
            children: [
              SizedBox(
                height: 200,
                child: SingleChildScrollView(
                  scrollDirection: Axis.vertical,
                  child: Text(
                    pwd,
                    overflow: TextOverflow.clip,
                    softWrap: true,
                  ),
                ),
              ),
            ],
          )
        )
      ],
    );
  }
}

class UpdateText extends StatefulWidget {
  const UpdateText({Key? key}) : super(key: key);


  UpdateTextState createState() => UpdateTextState();
}

class UpdateTextState extends State<UpdateText> {
  String _textHolder = "";

  changeText() {

    setState(() {
      _textHolder = _pwd[0];
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        body: Center(
            child: Column(
            children: <Widget>[
              Container(
                  padding: const EdgeInsets.fromLTRB(20, 20, 20, 20),
                  child: Text(_textHolder,
                      style: const TextStyle(
                          fontSize: 21,
                      )
                  )
              ),
            ]
          )
        )
    );
  }
}

/*****************************************************************
 *
 *                       Page 3
 *      ListView mit Generierten & gespeicherten PW
 *
 *        siehe Firebase.dart Zeile 298 bis 374
 *
 *******************************************************************/


/*****************************************************************
 *
 *                   Page "Settings"
 *
 *****************************************************************/

class Settings extends StatefulWidget {
  const Settings({Key? key}) : super(key: key);

  @override
  _Settings createState() => _Settings();
}

class _Settings extends State<Settings>{
  @override
  Widget build(BuildContext context) {
    return  SafeArea(
      child: Scaffold(
        appBar: AppBar(
          title: const Text("Einstellungen"),
        ),
        body: Column(
          children: [
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceAround,
              children: [
                const Text(
                  "Offline Datenbank",
                ),
                Switch(
                    value: _offlinemode,
                    onChanged: (value){
                      setState(() {
                        _offlinemode = value;
                      });
                    }
                ),
              ],
            ),
          ],
        )
      ),
    );
  }
}