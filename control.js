// Light
var btn1 = document.getElementById("example_01");
btn1.onclick = function(){
  if (document.getElementById("example_01").checked){
    document.getElementById("d01_img").src = "./img/densang.png"  
    firebase.database().ref("/TT_IoT").update({
      "BULB_01": "ON"
    })
  } else {
    document.getElementById("d01_img").src = "./img/dentat.png"
    firebase.database().ref("/TT_IoT").update({
      "BULB_01": "OFF"
    })
  }
}

// Fan
var btn2 = document.getElementById("example_02");
btn2.onclick = function(){
  if (document.getElementById("example_02").checked){
    document.getElementById("d02_img").src = "./img/quatchay.png"  
    firebase.database().ref("/TT_IoT").update({
      "BULB_01": "ON"
    })
  } else {
    document.getElementById("d02_img").src = "./img/quatdungim.png"
    firebase.database().ref("/TT_IoT").update({
    })
  }
}

// TV
var btn3 = document.getElementById("example_03");
btn3.onclick = function(){
  if (document.getElementById("example_03").checked){
    document.getElementById("d03_img").src = "./img/tivion.png"  
    firebase.database().ref("/TT_IoT").update({
      "BULB_01": "ON"
    })
  } else {
    document.getElementById("d03_img").src = "./img/tivioff.png"
    firebase.database().ref("/TT_IoT").update({
    })
  }
}

// Lock
var btn4 = document.getElementById("example_04");
btn4.onclick = function(){
  if (document.getElementById("example_04").checked){
    document.getElementById("d04_img").src = "./img/lock.png"  
    firebase.database().ref("/TT_IoT").update({
      "BULB_01": "ON"
    })
  } else {
    document.getElementById("d04_img").src = "./img/unlocked.png"
    firebase.database().ref("/TT_IoT").update({
    })
  }
}

// Air
var btn5 = document.getElementById("example_05");
btn5.onclick = function(){
  if (document.getElementById("example_05").checked){
    document.getElementById("d05_img").src = "./img/airrun.png"  
    firebase.database().ref("/TT_IoT").update({
      "BULB_01": "ON"
    })
  } else {
    document.getElementById("d05_img").src = "./img/airstop.png"
    firebase.database().ref("/TT_IoT").update({
    })
  }
}


