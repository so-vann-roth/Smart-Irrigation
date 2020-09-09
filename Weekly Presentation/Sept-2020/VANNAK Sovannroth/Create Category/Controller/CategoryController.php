<?php

namespace Modules\Admin\Http\Controllers;

use Illuminate\Contracts\Support\Renderable;
use Illuminate\Http\Request;
use Illuminate\Routing\Controller;
use DB;
class CategoryController extends Controller
{
    public function __construct()
    {
        $this->middleware('auth');
    }
    public function index()
    {
        $data['cats'] = DB::table('categories')
            ->where('active', 1)
            ->paginate(config('app.row'));
        return view('admin::categories.index', $data);
    }

    /**
     * Show the form for creating a new resource.
     * @return Renderable
     */
    public function create()
    {
        return view('admin::categories.create');
    }

    /**
     * Store a newly created resource in storage.
     * @param Request $request
     * @return Renderable
     */
    public function store(Request $request)
    {
        $request->validate([
            'name' => 'required|min:3'
           
        ]);
        $i = DB::table('categories')->insert($request->except('_token'));
        if($i)
        {
            return redirect()->route('category.create')
                ->with('success', config('app.success'));
        }
        else{
            return redirect()->route('category.create')
                ->with('error', config('app.error'))
                ->withInput();
        }
    }

    public function edit($id)
    {
        $data['cat'] = DB::table('categories')->find($id);
        return view('admin::categories.edit', $data);
    }

    /**
     * Update the specified resource in storage.
     * @param Request $request
     * @param int $id
     * @return Renderable
     */
    public function update(Request $request, $id)
    {
        $request->validate([
            'name' => 'required|min:3'
        ]);
        $data = array(
            'name' => $request->name
        );
        $i = DB::table('categories')
            ->where('id',$id)
            ->update($data);
        if($i)
        {
            return redirect()->route('category.edit', $id)
                ->with('success', config('app.success'));
        }
        else{
            return redirect()->route('category.edit', $id)
                ->with('error', config('app.error'))
                ->withInput();
        }
    }

    public function delete($id)
    {
        $i = DB::table('categories')
            ->where('id', $id)
            ->update(['active'=>0]);
        if($i)
        {
            return redirect()->route('category.index')
                ->with('success', config('app.delete'));
        }
        else{
            return redirect()->route('category.index')
                ->with('error', config('app.fail_del'));
        }     
    }
}
