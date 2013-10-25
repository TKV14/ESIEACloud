function signin(){ 

	if (document.getElementById('form_signin').style.display=='none'){ 
		document.getElementById('form_signin').style.display=''; 
		document.getElementById('bouton_signup').style.display='none';
	} else { 
		document.getElementById('form_signin').style.display='none'; 
		document.getElementById('bouton_signup').style.display='';

	} 
} 

function signup(){ 

	if (document.getElementById('form_signup').style.display=='none'){ 
		document.getElementById('form_signup').style.display=''; 
		document.getElementById('bouton_signin').style.display='none';

	} else { 
		document.getElementById('form_signup').style.display='none';
		document.getElementById('bouton_signin').style.display='';
 
	} 
} 