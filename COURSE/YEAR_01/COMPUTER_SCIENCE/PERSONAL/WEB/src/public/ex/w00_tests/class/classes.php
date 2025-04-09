<?php

  class Image
  {
    public static $folder = "src";
    public string $filename;
    public string $alt_text;

    public function __construct($filename, $alt_text)
    {
      $this->filename = $filename;
      $this->alt_text = $alt_text;
    }

    public function get_path(): string
    {
      return __DIR__ . DIRECTORY_SEPARATOR . $this->folder . DIRECTORY_SEPARATOR . $this->filename;
    }
  }

  class Article
  {
    public int $id;
    public string $genre;
    public string $header;
    public string $content;
    public string $date;
    public Image $img;

    public function __construct($id, $genre, $header, $content, $date, $img)
    {
      $this->id = $id;
      $this->img = $img;
      $this->genre = $genre;
      $this->header = $header;
      $this->content = $content;
      $this->date = $date;
    }

    public function format_header(): string
    {
      return "-$this->header-";
    }
  }