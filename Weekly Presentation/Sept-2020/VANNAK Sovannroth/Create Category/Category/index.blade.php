@extends('admin::layouts.master')
@section('header')
    <strong>Categories</strong>
@endsection
@section('content')
    <div class="card card-gray">
        <div class="toolbox">
            <a href="{{route('category.create')}}" class="btn btn-success btn-sm btn-oval">
                <i class="fa fa-plus-circle"></i> Create
            </a>
        </div>
        <div class="card-block">
            @component('admin::coms.alert')
            @endcomponent
            <table class="table table-sm table-bordered">
                <thead>
                    <th>#</th>
                    <th>Name</th>
                    <th>Actions</th>
                </thead>
                <tbody>
                    <?php
                        $pagex = @$_GET['page'];
                        if(!$pagex) $pagex = 1;
                        $i = config('app.row') * ($pagex-1) + 1;
                    ?>
                    @foreach($cats as $cat)
                        <tr>
                            <td>{{$i++}}</td>
                            
                            <td>{{$cat->name}}</td>
                            <td>
                                <a href="{{route('category.delete', $cat->id)}}" class="btn btn-danger btn-sm btn-oval" title="Delete" 
                                    onclick="return confirm('You want to delete?')">
                                    <i class="fa fa-trash"></i>
                                </a>
                                <a href="{{route('category.edit', $cat->id)}}" class="btn btn-primary btn-sm btn-oval" title="Edit">
                                    <i class="fa fa-edit"></i>
                                </a>
                            </td>
                        </tr>
                    @endforeach
                </tbody>
            </table>
            {{$cats->links()}}
        </div>
    </div>
@endsection 
@section('js')
    <script>
        $(document).ready(function(){
            $('#sidebar-menu li').removeClass('active open');
            $('#sidebar-menu li ul li').removeClass('active');

            $('#menu_config').addClass('active open');
            $('#collapse_config').addClass('collapse in');
            $('#menu_category').addClass('active');
        });
    </script>
@endsection