function signin(){ 

	if (document.getElementById('form_signin').style.display=='none'){ 
		document.getElementById('form_signin').style.display=''; 
		document.getElementById('bouton_signup').style.display='';
		document.getElementById('form_signup').style.display='none';
	} else { 
		document.getElementById('form_signin').style.display='none'; 
		document.getElementById('bouton_signup').style.display='';

	} 
} 

function signup(){ 

	if (document.getElementById('form_signup').style.display=='none'){ 
		document.getElementById('form_signup').style.display=''; 
		document.getElementById('form_signin').style.display='none'; 
		document.getElementById('bouton_signin').style.display='';

	} else { 
		document.getElementById('form_signup').style.display='none';
		document.getElementById('bouton_signin').style.display='';
 
	} 
} 

function Verif_longueur_erreur(champ, erreur)
{
   if(erreur)
      champ.style.backgroundColor = "#FE1B00";
   else
      champ.style.backgroundColor = "";
}

function Verif_longueur(champ)
{
   if(champ.value == "" || champ.value.length > 63)
   {
      Verif_longueur_erreur(champ, true);
      alert("Veuillez choisir un login et un mot de passe de moins de 63 caractères");
      return false;
   }
   else
   {
      Verif_longueur_erreur(champ, false);
      return true;
   }
}

function Confirm_password(champ)
{	
	if(champ.value != document.getElementById('password').value)
	{
		Verif_longueur_erreur(champ, true);
		alert("Confirmation du mot de passe invalide");
		return false;
	}
	else
	{
		Verif_longueur_erreur(champ, false);
		return true;
	}
}		

function Verif_signin(verif)
{
   var Login_Clear = Verif_longueur(verif.login);
   var Password_Clear = Verif_longueur(verif.password);
   
   if(Login_Clear && Password_Clear){
      return true;
	}
   else
   {
      return false;
   }
}

function Verif_signup(verif)
{
   var Login_Clear = Verif_longueur(verif.login);
   var Password_Clear = Verif_longueur(verif.password);
   var Password_Confirm_Clear = Confirm_password(verif.password_confirm);
   
   if(Login_Clear && Password_Clear && Password_Confirm_Clear){
      return true;
	}
   else
   {
      return false;
   }
}

