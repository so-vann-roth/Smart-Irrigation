<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use DB;
class ProjectController extends Controller
{
    
    public function index()
    {
        $data['com'] = DB::table('projects')->find(1);
        return view('projects.index', $data);
    }
    
    
}
