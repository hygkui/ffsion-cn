//file:login.js
// test thread
//background = Components.classes["@mozilla.org/thread-manager;1"].getService().newThread(0);
//main = Components.classes["@mozilla.org/thread-manager;1"].getService().mainThread;
var socket_id = 0;
var recv_flag = false ;
var recv_msg="";

//#################################################
// A test of Javascript
//################################################
function hellobak(){
    var fetionno = document.getElementById("user_account").value;
    var pswd = document.getElementById("user_pswd").value;
    alert("fetionno:" + fetionno + "pswd" + pswd );
};


//#################################################
// A test of MyComponents 
// when the login return is ok ,then open the mainWin.
//#################################################

function openMain(res){
    var fetionon = document.getElementById("user_account").value;
    var winTitle = "XYG mainWindow" ; 
    window.openDialog("main.xul","XYG","local,width=300,height=600",self,fetionon,res,winTitle);
    window.close();

};

//#################################################
// Login to MainWin
// register to Fetino Server.
//#################################################
function login(){
    document.getElementById("lbl_tip").value="";
        
    var fetionno = document.getElementById("user_account").value;
    var pswd = document.getElementById("user_pswd").value;
   
    var obj = Components.classes["@mozilla.org/fetion/fetionCom;1"].getService();
    obj = obj.QueryInterface(Components.interfaces.IFetionCom);

    obj.SetCallback(test);
    //alert("start to login");
    res = 0;//test of file save and xml parser. 2008-5-24. by ghh
        //obj.Login(fetionno , pswd ); //the Login function returns the socket ID .
    
    alert(res);
    if(res >= 0)
    {
        alert("login successful!,open mainWin ...");
        openMain(res);
    }else{
        document.getElementById("lbl_tip").value="wrong account or password .";
    }
};

  /* if u want a callback ,
  *declare it like var xx = function () {}; ,
  *if you declare like funtion xx(){};
  *it will not work !
  */
var test = function (str){
    alert(str);
};

function testCallback(){
   var obj = Components.classes["@mozilla.org/fetion/fetionCom;1"].getService(Components.interfaces.IFetionCom);
   obj.TestCallback( test );
};

