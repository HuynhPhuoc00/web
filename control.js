

// // Your web app's Firebase configuration
// const firebaseConfig = {
//   apiKey: "AIzaSyBny3WmaIL7xjGZrfLKgz5i8mps4sMbsSU",
//   authDomain: "tt-iot-ute.firebaseapp.com",
//   databaseURL: "https://tt-iot-ute-default-rtdb.firebaseio.com",
//   projectId: "tt-iot-ute",
//   storageBucket: "tt-iot-ute.appspot.com",
//   messagingSenderId: "999270078595",
//   appId: "1:999270078595:web:6ef84fd4903ea0dd2f23b6"
// };
// // Initialize Firebase
// firebase.initializeApp(firebaseConfig);


// // Auto load Temperature-------------------------
// firebase.database().ref("/TT_IoT/nhietdo").on("value",function(snapshot){
//   var nd = snapshot.val();  
//   document.getElementById("nhietdo").innerHTML = nd;
//   console.log(nd);
// });

// //Update Bulb status-----when reload website-------
// firebase.database().ref("/TT_IoT").get().then((snapshot) => {
//   if(snapshot.exists()){
//     console.log(snapshot.val())

//     var bulb_01_status = snapshot.val()
//     if (bulb_01_status["BULB_01"] == "ON")
//       document.getElementById("d01_img").src = "./img/densang.png"
//     else
//       document.getElementById("d01_img").src = "./img/dentat.png"
//   }
//   else
//     console.log("No data available!")
// })

//Den 01-------------------------------------------------------

// var d01_on = document.getElementById("d01_on");
// var d01_off = document.getElementById("d01_off");



// d01_on.onclick = function(){
//     console.log("On");
//     document.getElementById("d01_img").src = "./img/light_bulb_on.png"
    
//     firebase.database().ref("/TT_IoT").update({
//     "BULB_01": "ON"
//   })
// }

// d01_off.onclick = function(){
// 	document.getElementById("d01_img").src = "./img/light_bulb_off.png"
	
//   firebase.database().ref("/TT_IoT").update({
// 		"BULB_01": "OFF"
// 	})
// }

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

var btn4 = document.getElementById("example_04");
btn4.onclick = function(){
  if (document.getElementById("example_04").checked){
    document.getElementById("d04_img").src = "./img/unlocked.png"  
    firebase.database().ref("/TT_IoT").update({
      "BULB_01": "ON"
    })
  } else {
    document.getElementById("d04_img").src = "./img/lock.png"
    firebase.database().ref("/TT_IoT").update({
    })
  }
}

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

var btn7 = document.getElementById("example_07");
btn7.onclick = function(){
  if (document.getElementById("example_07").checked){
    document.getElementById("d07_img").src = "./img/kitchenon.png"  
    firebase.database().ref("/TT_IoT").update({
      "BULB_01": "ON"
    })
  } else {
    document.getElementById("d07_img").src = "./img/kitchenoff.png"
    firebase.database().ref("/TT_IoT").update({
    })
  }
}

var btn8 = document.getElementById("example_04");
btn8.onclick = function(){
  if (document.getElementById("example_04").checked){
    document.getElementById("d08_img").src = "./img/ovenon.png"  
    firebase.database().ref("/TT_IoT").update({
      "BULB_01": "ON"
    })
  } else {
    document.getElementById("d08_img").src = "./img/ovenoff.png"
    firebase.database().ref("/TT_IoT").update({
    })
  }
}



