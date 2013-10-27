function form_upload(){ 

	if (document.getElementById('form_upload').style.display=='none'){ 
		document.getElementById('form_upload').style.display='block'; 
		document.getElementById('bouton_upload').style.display='';
		document.getElementById('tableau').style.display='none';
	} else { 
		document.getElementById('form_upload').style.display='none'; 
		document.getElementById('tableau').style.display='';

	} 
} 

function liste_fichiers(){ 

	if (document.getElementById('form_upload').style.display=='block'){ 
		document.getElementById('form_upload').style.display='none'; 
		document.getElementById('tableau').style.display='';
	} 
} 