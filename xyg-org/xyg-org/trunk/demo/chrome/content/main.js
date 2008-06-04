var fetionNo= 0;
var socketId= -1 ;
var tilte = "";
function about()
{
	alert("Thanks to Ghh");
};

function init(){         
	fetionNo  =window.arguments[1];
	socketId  = window.arguments[2] ;
	title =  window.arguments[3] ;
    document.getElementById("myFetionno").value=  fetionNo ;
};

function sendMsg(FriendNo , Msg){
	var obj = Components.classes["@mozilla.org/fetion/fetionCom;1"].getService();
    obj = obj.QueryInterface(Components.interfaces.IFetionCom);
    res=obj.SendAMsg(socketId  , fetionNo  , FriendNo ,  Msg);
    
    if(res==0){
    	alert("success to send a message to sb.");
    }else{
    	alert("please to check your connect!");
    }       
};

function sendToMe(){
    var no="684718584";
    sendMsg(no,"hello");
};

function getUserInfo(){
	window.openDialog( "perInfo.xul","xxx " ,"local,width=200,height=300", self , fetionNo ,  socketId );         
    
};

function closeConnect(){
	var obj = Components.classes["@mozilla.org/fetion/fetionCom;1"].getService();

    obj = obj.QueryInterface(Components.interfaces.IFetionCom);
	res=obj.CloseSocket(  socketId );
	if (res != 0){
		alert("err occurred during disconneting the socket");
	}
};


function exit(){
    window.close();
};

//==========================================
//   about window
//==========================================

function openChat( ){		
	    window.openDialog( "chat.xul","chat .. " ,"local,width=400,height=300", self , fetionNo ,  socketId );            
};


function setPrefer(){
	     window.openDialog( "prefer.xul","preference ... " ,"local,width=400,height=300", self ); 
};

function help(){
     alert("call 110 in China , OR \r\n call 911 in the USA");
};

function addNewFriend(){
    alert("add a new friend");
}

function showAllFriends(){
    alert("show all friends");
};
function showOnlineFriends(){
    alert("shwo online friends");
};
