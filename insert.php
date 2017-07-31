#! /bin/php

<?php
class insert{
  private $_bdd;
  public function __construct()	{
  		try {
  			$this->_bdd=new PDO('mysql:host=localhost;dbname=test;charset=utf8','pi','r@spi');
  		}
  		catch(Exception $e){
        die('Erreur : '.$e->getMessage());
      }
  	}

  public function traitmentFile(){
    $da = NULL;
    $hu = NULL;
    $te = NULL;
    $pie = NULL;
    //$ha = NULL;
    //$i = 0;
    $file = fopen('30072017.log','r');
  //  while (!feof($file)){
      for ($i=0 ; $i < 4 ; $i++ ) {
        $ligne = fgets($file);
        $rest = substr($ligne,0,4);
        switch ($rest) {
          case "das1":
            $da= substr($ligne,5,16);
            $piece= substr($ligne,2,3);
            break;
          case "hus1":
            $hu = substr($ligne,6,7);
            break;
          case "tes1":
            $te = substr($ligne,6,7);
            break;
        /*  case 'has1'
            $ha = substr($ligne,6,7);
            break;*/

          default:
            # code...
            break;

          }
      }
      $sql = $this->_bdd->prepare('INSERT INTO test (dhtPiece,humidite,temperature,datetim) VALUE (:pie,:hu,:te,:da) ');
      $sql->execute(array( 'pie'=> $piece,
                           'hu' => $hu,
                           'te' => $te,
                           'da' => $da));
      printf("requète complete\n");
      echo "da ".$da."pie ".$piece."hu ".$hu."te ".$te."\n";
    //}
      fclose($file);
    }//fin de function


    }//fin de classe

  /*
  $req = $this->_bdd->prepare('SELECT id FROM t_utilisateur WHERE identifiant = :pseudo AND motdepasse = :pass');
  		$req->execute(array(
      						'pseudo' => $_POST['identifier'],
      						'pass' => $_POST['pass']));

  */
  //exec :php insert.php
  $insertion = new insert;
  print("Hello World !\n");
  $insertion->traitmentFile();
?>
