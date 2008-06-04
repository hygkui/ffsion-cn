var fetionNo= 0;
var  socketId= -1 ;
 var charset="UTF-8";
var     repChar=Components.interfaces.nsIConverterInputStream.DEFAULT_REPLACEMENT_CHARACTER;;
var d=new Date();
function init(){    

	fetionNo  =window.arguments[1];
	socketId  = window.arguments[2] ;
	title  =   "chating with " + fetionNo;	
};

function getCurrentTime(){
   var  year=d.getFullYear().toString();
   var  month=(d.getMonth()+1).toString();
   var  day=d.getDate().toString();
   var  hour=d.getHours().toString();
   var  minu=d.getMinutes().toString();
   var  seco=d.getSeconds().toString();
   rtnStr= year+"-"+month+"-" +day+" "+hour+":"+minu+":"+seco;
   return rtnStr;

}

var addRecvMsg=function(fromFeNo,msg)
{
   dateStr=getCurrentTime();
    
   
   document.getElementById('conver').value = 
        document.getElementById('conver').value  +
        "\r\n"+
        dateStr + "  " + 
        fromFeNo + " says:"+
        "\r\n" + msg ;
};

function sendMsg(){
    msg=document.getElementById('input').value;
   
    dateStr=getCurrentTime();

    document.getElementById('conver').value = 
        document.getElementById('conver').value  +
        "\r\n"+
        dateStr + "  " + 
        fetionNo + " says:"+
        "\r\n" + msg ;

    document.getElementById('input').value="";
    //link to the xpcom and exec sengMsg(msg)

}

function saveChat(){
    //link to nsFile xpcom. write the conver's value to the file named with the date.2008-5-18 21:43:10
    alert("save chat now");
     saveFile();
    //file read and write.
    //
}
function openFile(){
    var aFile = Components.classes["@mozilla.org/file/local;1"].
                    createInstance(Components.interfaces.nsILocalFile);
    aFile.initWithPath("/home/guohuan/ffsion/demo/chrome/content/data/");

    const nsIFilePicker = Components.interfaces.nsIFilePicker;

    var fp = Components.classes["@mozilla.org/filepicker;1"]
                       .createInstance(nsIFilePicker);
    fp.displayDirectory=aFile;
    fp.init(window, "Dialog Title", nsIFilePicker.modeOpen);
    fp.appendFilters(nsIFilePicker.filterAll | nsIFilePicker.filterText);
     
     
    
    var rv = fp.show();
    if (rv == nsIFilePicker.returnOK) {
        var file = fp.file;
        var fis = Components.classes["@mozilla.org/network/file-input-stream;1"]
                  .createInstance(Components.interfaces.nsIFileInputStream);
        fis.init(file, -1, -1, 0);

        var cis = Components.classes["@mozilla.org/intl/converter-input-stream;1"]
                  .createInstance(Components.interfaces.nsIConverterInputStream);
        cis.init(fis, charset, 1024, repChar);

        var remain = '';
        var str = {};
        while (cis.readString(4096, str) != 0) {
            remain += str.value;
        }
        cis.close();
        fis.close();

        document.getElementById('hist').value=remain;
        document.getElementById('hist').hidden=false;
       
        
    }
    fp = null;
    aFile=null;
    file=null;
}

function saveFile() {
	
	var rename=getCurrentTime();
	var file=null;
//	var thefile=null;
//    if (rename || file == null) {
//        var nsIFilePicker = Components.interfaces.nsIFilePicker;
//        var fp = Components.classes["@mozilla.org/filepicker;1"].createInstance(nsIFilePicker);
//        fp.init(window, "Select a file to save", nsIFilePicker.modeSave);
//        var res = fp.show();
//        if (res == nsIFilePicker.returnOK) {
//            file = fp.file;
//        }
//        if (res == nsIFilePicker.returnReplace) {
//            thefile = fp.file;
//            thefile.remove(false);
//        }
//        fp = null;
//    }
    
    var content =  document.getElementById('conver').value;
    alert(content.length);
    if(content.length < 1 ) return;
    
     var file = Components.classes["@mozilla.org/file/local;1"].
                    createInstance(Components.interfaces.nsILocalFile);
    file.initWithPath("/home/guohuan/ffsion/demo/chrome/content/data/"+rename);
    
    
    if (file == null) return;

    var fos = Components.classes["@mozilla.org/network/file-output-stream;1"]
              .createInstance(Components.interfaces.nsIFileOutputStream);
    fos.init(file, -1, -1, 0);

    var cos = Components.classes["@mozilla.org/intl/converter-output-stream;1"]
              .createInstance(Components.interfaces.nsIConverterOutputStream);
    cos.init(fos, charset, 0, repChar);

    cos.writeString(content);

    cos.close();
    fos.close();
  
}


