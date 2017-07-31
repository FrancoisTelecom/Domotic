#! /bin/php

<?php
class insert{
  private $_bdd;
  public function __construct()	{
  		try {
  			$this->_bdd=new PDO('mysql:host=localhost;dbname=station_meteo_local;charset=utf8','pi','r@spi');
  		}
  		catch(Exception $e){
        die('Erreur : '.$e->getMessage());
      }
  	}
}

  /*
  $req = $this->_bdd->prepare('SELECT id FROM t_utilisateur WHERE identifiant = :pseudo AND motdepasse = :pass');
  		$req->execute(array(
      						'pseudo' => $_POST['identifier'],
      						'pass' => $_POST['pass']));

  */
  //exec :php insert.php
  print("Hello World !\n");
?>
