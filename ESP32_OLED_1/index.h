const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang = "en">
  <head>
    <title>ESP32.html</title>
    <meta charset = "UTF-8" />
  </head>
  <body>
  <div>
    <div style="width:25% ;float: left;">
    <label>SSID &ensp;&emsp;</label>
    <input type="text" id="ssid"><br><br>
    <label>Password</label>
    <input type="password" id="pass">
    <input type="checkbox" onclick="myFunction()">Show</input>
    </div>
  </body>
</html>
<script>
  var currency = ["BTCBTC", "ETHBTC", "LTCBTC", "BNBBTC", "NEOBTC", "BCCBTC", "GASBTC", "HSRBTC", "MCOBTC", "WTCBTC", "LRCBTC", "QTUMBTC", "YOYOBTC", "OMGBTC", "ZRXBTC", "STRATBTC", "SNGLSBTC", "BQXBTC", "KNCBTC", "FUNBTC", "SNMBTC", "IOTABTC", "LINKBTC", "XVGBTC", "SALTBTC", "MDABTC", "MTLBTC", "SUBBTC", "EOSBTC", "SNTBTC", "ETCBTC", "MTHBTC", "ENGBTC", "DNTBTC", "ZECBTC", "BNTBTC", "ASTBTC", "DASHBTC", "OAXBTC", "ICNBTC", "BTGBTC", "EVXBTC", "REQBTC", "VIBBTC", "TRXBTC", "POWRBTC", "ARKBTC", "XRPBTC", "MODBTC", "ENJBTC", "STORJBTC", "VENBTC", "KMDBTC", "RCNBTC", "NULSBTC", "RDNBTC", "XMRBTC", "DLTBTC", "AMBBTC", "BATBTC", "BCPTBTC", "ARNBTC", "GVTBTC", "CDTBTC", "GXSBTC", "POEBTC", "QSPBTC", "BTSBTC", "XZCBTC", "LSKBTC", "TNTBTC", "FUELBTC", "MANABTC", "BCDBTC", "DGDBTC", "ADXBTC", "ADABTC", "PPTBTC", "CMTBTC", "XLMBTC", "CNDBTC", "LENDBTC", "WABIBTC", "TNBBTC", "WAVESBTC", "GTOBTC", "ICXBTC", "OSTBTC", "ELFBTC", "AIONBTC", "NEBLBTC", "BRDBTC", "EDOBTC", "WINGSBTC", "NAVBTC", "LUNBTC", "TRIGBTC", "APPCBTC", "VIBEBTC", "RLCBTC", "INSBTC", "PIVXBTC", "IOSTBTC", "CHATBTC", "STEEMBTC", "NANOBTC", "VIABTC", "BLZBTC", "AEBTC", "RPXBTC", "NCASHBTC", "POABTC", "ZILBTC", "ONTBTC", "STORMBTC", "XEMBTC", "WANBTC", "WPRBTC", "QLCBTC", "SYSBTC", "GRSBTC", "CLOAKBTC", "GNTBTC", "LOOMBTC", "BCNBTC", "REPBTC", "TUSDBTC", "ZENBTC", "SKYBTC", "CVCBTC", "THETABTC", "IOTXBTC", "QKCBTC", "AGIBTC", "NXSBTC", "DATABTC", "SCBTC", "NPXSBTC", "KEYBTC", "NASBTC", "MFTBTC", "DENTBTC", "ARDRBTC", "HOTBTC", "VETBTC", "DOCKBTC", "POLYBTC", "PHXBTC", "HCBTC", "GOBTC", "PAXBTC", "RVNBTC", "DCRBTC", "MITHBTC", "BCHABCBTC", "BCHSVBTC", "RENBTC", "BTTBTC", "ONGBTC", "FETBTC", "CELRBTC", "MATICBTC", "ATOMBTC", "PHBBTC", "TFUELBTC", "ONEBTC", "FTMBTC", "BTCBBTC", "ALGOBTC", "ERDBTC", "DOGEBTC", "DUSKBTC", "ANKRBTC", "WINBTC", "COSBTC", "COCOSBTC", "TOMOBTC", "PERLBTC", "CHZBTC", "BANDBTC", "BEAMBTC", "XTZBTC", "HBARBTC", "NKNBTC", "STXBTC", "KAVABTC", "ARPABTC", "CTXCBTC", "BCHBTC", "TROYBTC", "VITEBTC", "FTTBTC", "OGNBTC", "DREPBTC", "TCTBTC", "WRXBTC", "LTOBTC", "MBLBTC", "COTIBTC", "STPTBTC", "SOLBTC", "CTSIBTC", "HIVEBTC", "CHRBTC", "MDTBTC", "STMXBTC", "PNTBTC", "DGBBTC", "COMPBTC", "SXPBTC", "SNXBTC", "IRISBTC", "MKRBTC", "DAIBTC", "RUNEBTC", "FIOBTC", "AVABTC", "BALBTC", "YFIBTC", "JSTBTC", "SRMBTC", "ANTBTC", "CRVBTC", "SANDBTC", "OCEANBTC", "NMRBTC", "DOTBTC", "LUNABTC", "IDEXBTC", "RSRBTC", "PAXGBTC", "WNXMBTC", "TRBBTC", "BZRXBTC", "WBTCBTC", "SUSHIBTC", "YFIIBTC", "KSMBTC", "EGLDBTC", "DIABTC", "UMABTC", "BELBTC", "WINGBTC", "UNIBTC", "NBSBTC", "OXTBTC", "SUNBTC", "AVAXBTC", "HNTBTC", "FLMBTC", "SCRTBTC", "ORNBTC", "UTKBTC", "XVSBTC", "ALPHABTC", "VIDTBTC", "AAVEBTC", "NEARBTC", "FILBTC", "INJBTC", "AERGOBTC", "AUDIOBTC", "CTKBTC", "BOTBTC", "AKROBTC", "AXSBTC", "HARDBTC", "RENBTCBTC", "STRAXBTC", "FORBTC", "UNFIBTC", "ROSEBTC", "SKLBTC", "SUSDBTC", "GLMBTC", "GRTBTC", "JUVBTC", "PSGBTC", "1INCHBTC", "REEFBTC", "OGBTC", "ATMBTC", "ASRBTC", "CELOBTC", "RIFBTC", "BTCSTBTC", "TRUBTC", "CKBBTC", "TWTBTC", "FIROBTC", "LITBTC", "SFPBTC"];
  var tab = "<div style=\"width:65%; float: right;\"><table cellspacing=\"0\" rules=\"all\" border=\"1\" id=\"Table1\" style=\"border-collapse: collapse;  display: block; height: 200px; overflow-y: scroll; overflow-x: scroll;\"><tr><th>Select Curreny</th><th>Currency</th><th>Set Value</th></tr>"
  for(var i=0; i<currency.length-1; i++){
     tab = tab + "<tr><td><input class=\"ch\" type=\"checkbox\"/></td><td>"+currency[i].slice(0, -3)+"</td><td><input id="+i+" type=\"number\"/></td></tr>"
  }
  tab = tab + "</table><button id=\"sub\" onclick=\"get_data()\"> Submit </button></div></div>"
  
  document.write(tab)
  function myFunction() {
  var x = document.getElementById("pass");
  if (x.type === "password") {
    x.type = "text";
  } else {
    x.type = "password";
  }
}
  
  function get_data(){
    var grid = document.getElementById("Table1");
    var checkBoxes = grid.getElementsByClassName("ch");
    var selects = "";
    var selects_vals = "";
    var count = 0;
    
     for (var i = 0; i < checkBoxes.length; i++) {
      if (checkBoxes[i].checked) {
        x = i.toString();
        var row = checkBoxes[i].parentNode.parentNode;
        selects += row.cells[1].innerHTML  + ";";
        message = document.getElementById(x).value;
        count ++;
        if(message == "")
          selects_vals += "0;";
        else
          selects_vals += message + ";";
        
        message = "";
      }
    }
    var ssid = document.getElementById("ssid").value;
    var pass = document.getElementById("pass").value;
    if(pass == "" || ssid == "" || selects == ""){
      alert("Something is Missing");
    }
    else{
      var xhttp = new XMLHttpRequest();
      xhttp.open("POST", "/update", true);
      xhttp.setRequestHeader("Content-Type", "application/json");
      var data = JSON.stringify({ "ssid": ssid, "pass": pass, "currencies": selects, "vals": selects_vals, "len":count});  
      xhttp.send(data);
    }
    
  }
  
</script>
)rawliteral";
