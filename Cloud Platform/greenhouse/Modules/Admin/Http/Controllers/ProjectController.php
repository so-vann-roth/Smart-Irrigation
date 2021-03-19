<?php

namespace Modules\Admin\Http\Controllers;

use Illuminate\Contracts\Support\Renderable;
use Illuminate\Http\Request;
use Illuminate\Routing\Controller;
use DB;
class ProjectController extends Controller
{
    public function __construct()
    {
        $this->middleware('auth');
    }
    public function index()
    {
        $data['com'] = DB::table('projects')->find(1);
        return view('admin::projects.index', $data);
    }
     
    public function edit($id)
    {
        $data['com'] = DB::table('projects')->find(1);
        return view('admin::projects.edit', $data);
    }

    public function save(Request $request)
    {
        $data = array(
            'title' => $request->title,
            'address' => $request->address,
            'description' => $request->description,
            
        );
        if($request->photo)
        {
            $data['logo'] = $request->file('photo')->store('uploads/projects', 'custom');
        }
        $i = DB::table('projects')->where('id', 1)
            ->update($data);
        if($i)
        {
            return redirect()->route('project.index')
                ->with('success', config('app.success'));
        }
        else{
            return redirect()->route('project.edit', 1)
                ->with('error', config('app.error'));
        }
    }


}
