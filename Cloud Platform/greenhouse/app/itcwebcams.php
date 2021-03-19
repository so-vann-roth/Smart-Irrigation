<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class itcwebcams extends Model
{
    protected $fileable=['title', 'description', 'file'];
}
