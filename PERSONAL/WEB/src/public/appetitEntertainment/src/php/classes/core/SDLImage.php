<?php

  declare(strict_types=1);

  namespace SDL\Classes\Core;



  /*
   * Responsible for holding data in image filenames.
   */

  class SDLImage
  {
    private function __construct(
      private string $filename
    ) {

    }



    /*
     */

    public static function create(?string $filename): static {
      return $filename !== null ? new static($filename) : null;
    }



    /*
     */

    public function getFileName() {
      return $this->filename;
    }



    /*
     */

    public static function getCleanFileName(string $filename): string {
      return substr($filename, 0, strrpos($filename, '.'));
    }



    /*
     */

    public function getFilenameCharacterInfo(): array {
      [$gender, $name] = preg_split("/[_]/", $this->filename, 2);

      return [
        preg_replace('/[_]/', ' ', $this->getCleanFileName($name)),
        $gender,
      ];
    }



    /*
     */

    public function getFilenameStatusName(): string {
      return $this->getCleanFileName(preg_split("/_status_/", $this->filename)[1]);
    }



    /*
     */

    public function setFileName(string $filename) {
      $this->filepath = $filename;
    }
  }
