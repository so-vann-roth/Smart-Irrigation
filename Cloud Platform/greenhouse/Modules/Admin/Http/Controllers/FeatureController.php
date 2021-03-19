<?php

namespace Modules\Admin\Http\Controllers;

use Illuminate\Contracts\Support\Renderable;
use Illuminate\Http\Request;
use Illuminate\Routing\Controller;
use DB;
class FeatureController extends Controller
{
    public function __construct()
    {
        $this->middleware('auth');
    }
    /**
     * Display a listing of the resource.
     * @return Renderable
     */
    public function index()
    {
        $data['features'] = DB::table('features')
            ->where('active', 1)
            ->paginate(config('app.row'));
        return view('admin::features.index', $data);
    }

    /**
     * Show the form for creating a new resource.
     * @return Renderable
     */
    public function create()
    {
        return view('admin::features.create');
    }

    /**
     * Store a newly created resource in storage.
     * @param Request $request
     * @return Renderable
     */
    public function store(Request $request)
    {
        $request->validate([
            'title' => 'required',
           
        ]);
        $i = DB::table('features')->insert($request->except('_token'));
        if($i)
        {
            return redirect()->route('feature.create')
                ->with('success', config('app.success'));
        }
        else{
            return redirect()->route('feature.create')
                ->with('error', config('app.error'))
                ->withInput();
        }
    }

    public function edit($id)
    {
        $feature = DB::table('features')->find($id);
        return view('admin::features.edit', compact('feature'));
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
            'title' => 'required'
           
        ]);
        $data = $request->except('_token', '_method');
        $i = DB::table('features')
            ->where('id', $id)
            ->update($data);

        if($i)
        {
            return redirect()->route('feature.index')
                ->with('success', config('app.success'));
        }
        else{
            return redirect()->route('feature.edit', $id)
                ->with('error', config('app.error'));
      
        }
    }

    public function delete($id)
    {
        $i = DB::table('features')
            ->where('id', $id)
            ->update(['active'=>0]);
        if($i)
        {
            return redirect()->route('feature.index')
                ->with('success', config('app.delete'));
        }
        else{
            return redirect()->route('feature.index')
                ->with('error', config('app.fail_del'));
        }     
    }
}
