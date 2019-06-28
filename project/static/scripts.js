$(document).ready(function(){
//https://developers.google.com/books/docs/v1/using
//https://plus.google.com/+CodingGeeks

   $("#form1").submit(function(){

   	  var find = $("#books").val();
   	  if(find == "")
   	  {
   	  	alert("Please enter something in the field");
   	  }
   	  else{
   	  var url = "";
      var title = "";
      var img = "";
      var author = "";

   	  $.get("https://www.googleapis.com/books/v1/volumes?q="+find,function(response){

            //goes through the entire object's length given to us by api and saves object info in different variables that are added
            //into a list which references search.html
          for(i = 0; i<response.items.length;i++)
          {
           title=$('<h5 class="center-align black-text">' + response.items[i].volumeInfo.title + '</h5>');
           author=$('<h5 class="center-align green-text"> By:' + response.items[i].volumeInfo.authors + '</h5>');
           img = $('<img class="aligning card z-depth-7" id="dynamic"><br><a href=' + response.items[i].volumeInfo.infoLink + '><button id="imagebutton" class="btn red aligning">Read</button></a>');
           url= response.items[i].volumeInfo.imageLinks.thumbnail;
           title.appendTo('#work');
           author.appendTo('#work');
           img.appendTo('#work');
          }
   	  });

      }
      return false;
   });

});