var fetionNo="";
var socketId= 0 ;

function init(){
	fetionNo  =window.arguments[1];
	socketId  = window.arguments[2] ;
	title =fetionNo +  "'s info  " ;	
}
function getPerInfo(){ 
    var obj = Components.classes["@mozilla.org/fetion/fetionCom;1"].getService();
    obj = obj.QueryInterface(Components.interfaces.IFetionCom);
    res = obj.GetUserInfo(  socketId   , fetionNo );
    alert(res);
};

function setPerInfo(){
    alert("set PerInfo");
};


