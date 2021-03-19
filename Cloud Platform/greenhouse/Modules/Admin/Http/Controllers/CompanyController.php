<?php

namespace Modules\Admin\Http\Controllers;

use Illuminate\Contracts\Support\Renderable;
use Illuminate\Http\Request;
use Illuminate\Routing\Controller;
use DB;
class CompanyController extends Controller
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
        $data['com'] = DB::table('companies')->find(1);
        return view('admin::companies.index', $data);
    }
     
    public function edit($id)
    {
        $data['com'] = DB::table('companies')->find(1);
        return view('admin::companies.edit', $data);
    }

    public function save(Request $request)
    {
        $data = array(
            'name' => $request->name,
            'phone' => $request->phone,
            'email' => $request->email,
            'address' => $request->address,
            'description' => $request->description
        );
        if($request->photo)
        {
            $data['logo'] = $request->file('photo')->store('uploads/companies', 'custom');
        }
        $i = DB::table('companies')->where('id', 1)
            ->update($data);
        if($i)
        {
            return redirect()->route('company.index')
                ->with('success', config('app.success'));
        }
        else{
            return redirect()->route('company.edit', 1)
                ->with('error', config('app.error'));
        }
    }


}
