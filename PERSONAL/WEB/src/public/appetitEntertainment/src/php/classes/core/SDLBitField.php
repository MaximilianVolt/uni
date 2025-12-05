<?php

  declare(strict_types=1);

  namespace SDL\Classes\Core;



  trait SDLBitField
  {
    private int $flags;



    /*
     */

    public function getFlags(): int {
      return $this->flags;
    }



    /*
     */

    public function getFlag(int $index): bool {
      return (bool) ($this->flags >> $index & 1);
    }



    /*
     */

    public function getMaskRegion(int $size, int $offset = 0): int {
      return $this->mask >> $offset & (1 << $size) - 1;
    }



    /*
     */

    public function getMaskRegionBut(int $size, int $offset = 0): int {
      return $this->mask >> $offset & ~((1 << $size) - 1);
    }


    /*
     */

    public function setFlag(int $index, bool $value = true): bool {
      $this->flags = $this->flags & ~(1 << $index) | $value << $index;
      return $value;
    }



    /*
     */

    public function setMaskRegion(int $value, int $size, int $offset = 0): int {
      $this->flags = $this->flags & ~((1 << $size) - 1 << $offset) | $value << $offset;
      return $value << $offset;
    }
  }
